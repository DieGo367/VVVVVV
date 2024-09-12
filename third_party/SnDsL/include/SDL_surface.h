#pragma once
#include "SDL_rect.h"
#include "SDL_pixels.h"

typedef struct SDL_Surface
{
	Uint32 flags;
	SDL_PixelFormat *format;
	int w, h;
	int pitch;
	void *pixels;
} SDL_Surface;

SDL_Surface *SDL_CreateRGBSurface(uint32_t flags, int w, int h, int depth, uint32_t rmask, uint32_t gmask, uint32_t bmask, uint32_t amask);
SDL_Surface *SDL_CreateRGBSurfaceWithFormatFrom(void *pixels, int w, int h, int depth, int pitch, uint32_t format);
SDL_Surface *SDL_ConvertSurfaceFormat(SDL_Surface *src, uint32_t format, uint32_t flags);
void SDL_FreeSurface(SDL_Surface *surf);

#define SDL_SetSurfaceBlendMode(surf, mode) 0
#define SDL_GetSurfaceBlendMode(surf, mode)
#define SDL_LockSurface(surf) 0
#define SDL_UnlockSurface(surf)
#define SDL_BlitSurface(srcSurf, srcRect, destSurf, destRect) 0
#define SDL_BlitScaled(srcSurf, srcRect, destSurf, destRect) 0
