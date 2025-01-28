#pragma once
#include "SDL_rect.h"
#include "SDL_surface.h"

typedef struct SDL_Texture {
	uint16_t w, h;
	uint8_t bpp;
	uint8_t alphaMod;
	uint16_t colorMod;
	uint16_t *palette;
	uint8_t *data;
} SDL_Texture;
typedef struct SDL_Renderer {} SDL_Renderer;

typedef enum {
	SDL_TEXTUREACCESS_STATIC,		/**< Changes rarely, not lockable */
	SDL_TEXTUREACCESS_STREAMING,	/**< Changes frequently, lockable */
	SDL_TEXTUREACCESS_TARGET		/**< Texture can be used as a render target */
} SDL_TextureAccess;
typedef enum {
	SDL_ScaleModeNearest,
	SDL_ScaleModeLinear,
	SDL_ScaleModeBest
} SDL_ScaleMode;

SDL_Texture *SDL_CreateTexture(SDL_Renderer *rend, uint32_t format, int access, int w, int h);
SDL_Texture *SDL_CreateTextureFromSurface(SDL_Renderer *rend, SDL_Surface *surf);
int SDL_QueryTexture(SDL_Texture *tex, uint32_t *format, int *access, int *w, int *h);
#define SDL_UpdateTexture(tex, rect, pixels, pitch) 0
void SDL_DestroyTexture(SDL_Texture *tex);
#define SDL_SetTextureScaleMode(tex, scaleMode) 0
#define SDL_SetTextureBlendMode(tex, blendMode) 0
int SDL_SetTextureColorMod(SDL_Texture *tex, uint8_t r, uint8_t g, uint8_t b);
int SDL_SetTextureAlphaMod(SDL_Texture *tex, uint8_t a);
int SDL_GetTextureColorMod(SDL_Texture *tex, uint8_t *r, uint8_t *g, uint8_t *b);
int SDL_GetTextureAlphaMod(SDL_Texture *tex, uint8_t *alpha);

SDL_Texture *SnDsL_CreateTextureFromGRFData(int w, int h, int bpp, void *data, void *palette, int palCount);
SDL_Color SnDsL_ReadPixel(SDL_Texture *tex, int x, int y);

typedef enum {
	SDL_FLIP_NONE = 0,
	SDL_FLIP_HORIZONTAL, SDL_FLIP_VERTICAL
} SDL_RendererFlip;

#define SDL_CreateRenderer(win, idx, flags) ((SDL_Renderer *)1)
#define SDL_DestroyRenderer(rend)

#define SDL_RenderSetVSync(rend, vs)
#define SDL_SetRenderTarget(renderer, texture) 0
#define SDL_GetRenderTarget(rend) NULL
int SDL_GetRendererOutputSize(SDL_Renderer *rend, int *w, int *h);
#define SDL_RenderReadPixels(rend, rect, format, pixels, pitch) 0

#define SDL_SetRenderDrawBlendMode(renderer, blendmode) 0
int SDL_SetRenderDrawColor(SDL_Renderer *rend, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
int SDL_RenderDrawLine(SDL_Renderer *rend, int x1, int y1, int x2, int y2);
int SDL_RenderDrawPoint(SDL_Renderer *rend, int x, int y);
int SDL_RenderDrawPoints(SDL_Renderer *rend, const SDL_Point *points, int count);
int SDL_RenderDrawRect(SDL_Renderer *rend, const SDL_Rect *rect);
int SDL_RenderFillRect(SDL_Renderer *rend, const SDL_Rect *rect);
int SDL_RenderClear(SDL_Renderer *rend);
int SDL_RenderCopy(SDL_Renderer *rend, SDL_Texture *tex, const SDL_Rect *clip, const SDL_Rect *dst);
#define SDL_RenderCopyEx(rend, tex, srcRect, destRect, angle, center, flip) SDL_RenderCopy(rend, tex, srcRect, destRect)
#define SDL_RenderPresent(rend)

// blendmode.h

typedef enum {
	SDL_BLENDMODE_NONE = 0,
	SDL_BLENDMODE_BLEND
} SDL_BlendMode;