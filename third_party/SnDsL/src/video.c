#include "SDL_video.h"
#include "SDL_render.h"
#include "SDL_assert.h"
#include "SDL_rect.h"
#include "SDL_surface.h"

#include <nds/arm9/background.h>

#include <nds/debug.h>
#include <stdio.h>
#define nocashf(fmt, ...) do { \
	char message[120]; \
	int amt = snprintf(message, 120, fmt, __VA_ARGS__); \
	nocashWrite(message, amt); \
} while(0)

#include <ndsabi.h>
// Assumes 2-byte aligned. @param count number of u16 to write
void memset16(uint16_t *dst, uint16_t src, size_t count) {
	uint32_t word = src << 16 | src;
	uint32_t misaligned = (uint32_t) dst & 3;
	if (misaligned) dst++[0] = src;
	__ndsabi_wordset4(dst, (count * 2) - misaligned, word);
}

uint16_t renderDrawColor = 0;

static inline size_t textureDataSize(int w, int h, int bpp) {
	switch(bpp) {
	case 1:
		return (w*h + 7)/8;
	case 2:
		return (w*h + 3)/4;
	case 4:
		return (w*h + 1)/2;
	case 8:
		return w*h;
	case 16:
		return w*h*2;
	default:
		sassert(0, "Invalid bpp value");
	}
}

#define BGR15(r, g, b) (1 << 15 | ((b) >> 3) << 10 | ((g) >> 3) << 5 | (r) >> 3)

SDL_Texture *SnDsL_CreateTextureFromGRFData(int w, int h, int bpp, void *data, void *palette, int palCount) {
	SDL_Texture *tex = malloc(sizeof(SDL_Texture));
	if (tex) {
		*tex = (SDL_Texture){
			.w = w, .h = w, .bpp = bpp,
			.alphaMod = 255, .colorMod = 0xFFFF,
			.data = data, .palette = palette
		};
		if (tex->palette) tex->palette[0] = palCount;
	}
	return tex;
}

int SDL_QueryTexture(SDL_Texture *tex, uint32_t *format, int *access, int *w, int *h) {
	if (!tex) return -1;
	if (format) *format = tex->bpp;
	if (access) *access = SDL_TEXTUREACCESS_STATIC;
	if (w) *w = tex->w;
	if (h) *h = tex->h;
	return 0;
}

SDL_Color SnDsL_ReadPixel(SDL_Texture *tex, int x, int y) {
	SDL_Color colorStruct = {0, 0, 0, 0};
	if (tex && x >= 0 && x < tex->w && y >= 0 && y < tex->h) {
		int pixelIdx = y * tex->w + x;
		u16 color;
		if (tex->bpp == 16) color = ((u16 *)tex->data)[pixelIdx];
		else {
			u8 value = tex->data[pixelIdx * tex->bpp / 8] >> pixelIdx % (8 / tex->bpp) * tex->bpp & ((1 << tex->bpp) - 1);
			color = value ? tex->palette[value] : 0;
		}
		if (color & 1 << 15) {
			colorStruct.r = (color & 0b11111) << 3;
			colorStruct.g = (color >> 5 & 0b11111) << 3;
			colorStruct.b = (color >> 10 & 0b11111) << 3;
			colorStruct.a = 255;
		}
	}
	return colorStruct;
}

SDL_Texture *SDL_CreateTexture(SDL_Renderer *rend, uint32_t format, int access, int w, int h) {
	return NULL;
	// SDL_Texture *tex = malloc(sizeof(SDL_Texture) + ((w*h+7)/8)); // assume 1bpp for now
	// if (tex) {
	// 	tex->w = w, tex->h = h;
	// 	// memset(tex->palette, 0, sizeof(tex->palette) + (w*h/2));
	// }
	// if (!tex) nocashMessage("OOM CreateTexture");
	// return tex;
}

SDL_Texture *SDL_CreateTextureFromSurface(SDL_Renderer *rend, SDL_Surface *surf) {
	return NULL;
	// uint pixelsSize = (surf->w*surf->h/2);
	// SDL_Texture *tex = malloc(sizeof(SDL_Texture) + pixelsSize);
	// if (tex) {
	// 	tex->access = SDL_TEXTUREACCESS_STATIC;
	// 	tex->w = surf->w, tex->h = surf->h;
	// 	memset(tex->palette, 0, sizeof(tex->palette) + pixelsSize);
	// 	memcpy(tex->data, surf->pixels, pixelsSize);
	// }
	// if (!tex) nocashMessage("OOM CreateTextureFromSurface");
	// return tex;
}

void SDL_DestroyTexture(SDL_Texture *tex) {
	if (tex) {
		if (tex->palette) free(tex->palette);
		if (tex->data) free(tex->data);
		free(tex);
	}
}



// Provides the size of the render target. For now, this is hardcoded as the DS screen dimensions
int SDL_GetRendererOutputSize(SDL_Renderer *rend, int *w, int *h) {
	*w = SCREEN_WIDTH, *h = SCREEN_HEIGHT;
	return 0;
}

// Sets the draw color, converting to BGR15 while we're at it. This is global for now.
int SDL_SetRenderDrawColor(SDL_Renderer *rend, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
	renderDrawColor = a ? BGR15(r, g, b) : 0;
	return 0;
}

#define s(x) (((x)*4 + 3)/5)
// #define s(x) ((x)*4/5)

int SDL_RenderDrawLine(SDL_Renderer *rend, int x1, int y1, int x2, int y2) {
	uint16_t *gfx = bgGetGfxPtr(2);
	int dx = s(x2) - s(x1), dy = s(y2) - s(y1);
	if (abs(dx) > abs(dy)) {
		for (int x = s(x1); x != s(x2); x < s(x2) ? x++ : x--) {
			int y = x * dy / dx;
			if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) continue;
			gfx[y * SCREEN_WIDTH + x] = renderDrawColor;
		}
	} else {
		for (int y = s(y1); y != s(y2); y < s(y2) ? y++ : y--) {
			int x = y * dx / dy;
			if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) continue;
			gfx[y * SCREEN_WIDTH + x] = renderDrawColor;
		}
	}
	return 0;
}

int SDL_RenderDrawPoint(SDL_Renderer *rend, int x, int y) {
	if (s(x) >= 0 && s(x) < SCREEN_WIDTH && s(y) >= 0 && s(y) < SCREEN_HEIGHT) {
		bgGetGfxPtr(2)[s(y) * SCREEN_WIDTH + s(x)] = renderDrawColor;
	}
	return 0;
}
int SDL_RenderDrawPoints(SDL_Renderer *rend, const SDL_Point *points, int count) {
	uint16_t *gfx = bgGetGfxPtr(2);
	for (int i = 0; i < count; i++) {
		int x = points[i].x, y = points[i].y;
		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) continue;
		gfx[y * SCREEN_WIDTH + x] = renderDrawColor;
	}
	return 0;
}

int SDL_RenderDrawRect(SDL_Renderer *rend, const SDL_Rect *rect) {
	uint16_t *gfx = bgGetGfxPtr(2);
	int rx = 0, ry = 0, rw = SCREEN_WIDTH, rh = SCREEN_HEIGHT;
	if (rect) {
		rx = s(rect->x), ry = s(rect->y), rw = s(rect->w), rh = s(rect->h);
	}

	for (int y = 1; y < rh - 1; y++) {
		if (ry + y < 0 || ry + y >= SCREEN_HEIGHT) continue;

		if (rx >= 0 && rx < SCREEN_WIDTH) {
			gfx[(ry + y) * SCREEN_WIDTH + rx] = renderDrawColor;
		}
		if (rx + rw - 1 >= 0 && rx + rw - 1 < SCREEN_WIDTH) {
			gfx[(ry + y) * SCREEN_WIDTH + rx + rw - 1] = renderDrawColor;
		}
	}

	if (rx < 0) rw += rx, rx = 0;
	if (rx + rw > SCREEN_WIDTH) rw = SCREEN_WIDTH - rx;

	if (ry >= 0 && ry < SCREEN_HEIGHT) memset16(gfx + ry * SCREEN_WIDTH + rx, renderDrawColor, rw);
	if (ry + rh - 1 >= 0 && ry + rh - 1 < SCREEN_HEIGHT) memset16(gfx + (ry + rh - 1) * SCREEN_WIDTH + rx, renderDrawColor, rw);

	return 0;
}
int SDL_RenderFillRect(SDL_Renderer *rend, const SDL_Rect *rect) {
	uint16_t *gfx = bgGetGfxPtr(2);
	int rx = 0, ry = 0, rw = SCREEN_WIDTH, rh = SCREEN_HEIGHT;
	if (rect) {
		rx = s(rect->x), ry = s(rect->y), rw = s(rect->w), rh = s(rect->h);
		if (rx < 0) rw += rx, rx = 0;
		if (ry < 0) rh += ry, ry = 0;
		if (rx + rw > SCREEN_WIDTH) rw = SCREEN_WIDTH - rx;
		if (ry + rh > SCREEN_HEIGHT) rh = SCREEN_HEIGHT - ry;
	}
	if (rw == SCREEN_WIDTH) { // faster fill!
		memset16(gfx + ry * SCREEN_WIDTH, renderDrawColor, rw * rh);
	}
	else for (int y = 0; y < rh; y++) {
		memset16(gfx + ((ry + y) * SCREEN_WIDTH + rx), renderDrawColor, rw);
	}
	return 0;
}

int SDL_RenderClear(SDL_Renderer *rend) {
	// more performant just to ignore this for now
	// memset16(bgGetGfxPtr(2), renderDrawColor, SCREEN_WIDTH * SCREEN_HEIGHT);
	return 0;
}

static inline u16 colorMult(u16 target, u16 value) {
	u8 r = (target & 0b11111) * (value & 0b11111) / 0b11111;
	u8 g = (target >> 5 & 0b11111) * (value >> 5 & 0b11111) / 0b11111;
	u8 b = (target >> 10 & 0b11111) * (value >> 10 & 0b11111) / 0b11111;
	return 1 << 15 | b << 10 | g << 5 | r;
}

static inline u16 colorBlend(u16 base, u8 alpha, u16 top) {
	u8 r = ((base & 0b11111) * (255 - alpha) + (top & 0b11111) * alpha) / 255;
	u8 g = ((base >> 5 & 0b11111) * (255 - alpha) + (top >> 5 & 0b11111) * alpha) / 255;
	u8 b = ((base >> 10 & 0b11111) * (255 - alpha) + (top >> 10 & 0b11111) * alpha) / 255;
	return 1 << 15 | b << 10 | g << 5 | r;
}

int SDL_RenderCopy(SDL_Renderer *rend, SDL_Texture *tex, const SDL_Rect *clip, const SDL_Rect *dst) {
	if (!tex) return -1;
	if (tex->alphaMod == 0) return 0;
	
	int clipX = 0, clipY = 0, clipW = tex->w, clipH = tex->h;
	if (clip) {
		clipX = clip->x, clipY = clip->y, clipW = clip->w, clipH = clip->h;
	}
	int destX = 0, destY = 0, destW = SCREEN_WIDTH, destH = SCREEN_HEIGHT;
	if (dst) {
		destX = s(dst->x), destY = s(dst->y), destW = s(dst->w), destH = s(dst->h);
	}

	int offsX = destX < 0 ? -destX : 0;
	int offsY = destY < 0 ? -destY : 0;
	int rendW = (destW > SCREEN_WIDTH + offsX ? SCREEN_WIDTH + offsX : destW) + offsX;
	int rendH = (destH > SCREEN_HEIGHT + offsY ? SCREEN_HEIGHT + offsY : destH) + offsY;

	uint16_t *gfx = bgGetGfxPtr(2);
	for (int y = offsY; y < rendH; y++) {
		int ty = y * clipH / destH + clipY;
		for (int x = offsX; x < rendW; x++) {
			int tx = x * clipW / destW + clipX;
			int pixelIdx = ty * tex->w + tx;
			u16 color;
			if (tex->bpp == 16) {
				color = ((u16 *)tex->data)[pixelIdx];
				if ((color & BIT(15)) == 0) continue;
			// check for "5"bpp grayscale
			} else {
				u8 value = tex->data[pixelIdx * tex->bpp / 8] >> pixelIdx % (8 / tex->bpp) * tex->bpp & ((1 << tex->bpp) - 1);
				if (value == 0) continue;
				color = tex->palette[value];
			}
			color = colorMult(color, tex->colorMod);
			uint16_t *px = gfx + (destY + y) * SCREEN_WIDTH + (destX + x);
			if (tex->alphaMod != 255) *px = colorBlend(*px, tex->alphaMod, color);
			else *px = color;
		}
	}
	return 0;
}


int SDL_SetTextureColorMod(SDL_Texture *tex, uint8_t r, uint8_t g, uint8_t b) {
	if (!tex) return -1;
	tex->colorMod = BGR15(r, g, b);
	return 0;
}
int SDL_SetTextureAlphaMod(SDL_Texture *tex, uint8_t a) {
	if (!tex) return -1;
	tex->alphaMod = a;
	return 0;
}
int SDL_GetTextureColorMod(SDL_Texture *tex, uint8_t *r, uint8_t *g, uint8_t *b) {
	if (!tex) return -1;
	if (r) *r = (tex->colorMod & 0b11111) << 3;
	if (g) *g = (tex->colorMod >> 5 & 0b11111) << 3;
	if (b) *b = (tex->colorMod >> 10 & 0b11111) << 3;
	return 0;
}
int SDL_GetTextureAlphaMod(SDL_Texture *tex, uint8_t *alpha) {
	if (!tex) return -1;
	if (alpha) *alpha = tex->alphaMod;
	return 0;
}