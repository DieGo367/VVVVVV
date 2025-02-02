#pragma once
#include "SDL_rect.h"
#include "SDL_surface.h"

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

#define SDL_UpdateTexture(tex, rect, pixels, pitch) 0
#define SDL_SetTextureScaleMode(tex, scaleMode) 0
#define SDL_SetTextureBlendMode(tex, blendMode) 0

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
#define SDL_RenderCopyEx(rend, tex, srcRect, destRect, angle, center, flip) SDL_RenderCopy(rend, tex, srcRect, destRect)
#define SDL_RenderPresent(rend)

// blendmode.h

typedef enum {
	SDL_BLENDMODE_NONE = 0,
	SDL_BLENDMODE_BLEND
} SDL_BlendMode;