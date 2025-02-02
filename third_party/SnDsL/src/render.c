#include "SDL_render.h"
#include "SDL_rect.h"

#include <nds/arm9/background.h>

#include <ndsabi.h>
// Assumes 2-byte aligned. @param count number of u16 to write
void memset16(uint16_t *dst, uint16_t src, size_t count) {
	uint32_t word = src << 16 | src;
	uint32_t misaligned = (uint32_t) dst & 3;
	if (misaligned) dst++[0] = src;
	__ndsabi_wordset4(dst, (count * 2) - misaligned, word);
}

uint16_t renderDrawColor = 0;

#define BGR15(r, g, b) (1 << 15 | ((b) >> 3) << 10 | ((g) >> 3) << 5 | (r) >> 3)

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