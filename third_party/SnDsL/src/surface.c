#include "SDL_surface.h"

#include <nds/debug.h>
#include <stdio.h>
#define nocashf(fmt, ...) do { \
	char message[120]; \
	int amt = snprintf(message, 120, fmt, __VA_ARGS__); \
	nocashWrite(message, amt); \
} while(0)

SDL_Surface *SDL_CreateRGBSurface(uint32_t flags, int w, int h, int depth, uint32_t rmask, uint32_t gmask, uint32_t bmask, uint32_t amask) {
	return NULL;
	// SDL_Surface *surf = SDL_calloc(1, sizeof(SDL_Surface));
	// surf->flags = flags;
	// surf->format = SDL_calloc(1, sizeof(SDL_PixelFormat));
	// if (surf->format) {
	// 	surf->format->BitsPerPixel = depth;
	// 	surf->format->BytesPerPixel = depth / 8;
	// 	surf->format->Rmask = rmask;
	// 	surf->format->Gmask = gmask;
	// 	surf->format->Bmask = bmask;
	// 	surf->format->Amask = amask;
	// 	surf->w = w, surf->h = h;
	// 	surf->pixels = SDL_calloc(w*h/2, 1);
	// 	if (surf->pixels == NULL) {
	// 		free(surf->format);
	// 		free(surf);
	// 		surf = NULL;
	// 	}
	// }
	// else {
	// 	free(surf);
	// 	surf = NULL;
	// }
	// if (!surf) nocashMessage("OOM CreateRGBSurface");
	// return surf;
}

SDL_PixelFormat ARGB32 = {
	.BitsPerPixel = 32,
	.BytesPerPixel = 4,
	.Amask = 0xFF000000,
	.Rmask = 0x00FF0000,
	.Gmask = 0x0000FF00,
	.Bmask = 0x000000FF
};
SDL_PixelFormat ABGR32 = {
	.BitsPerPixel = 32,
	.BytesPerPixel = 4,
	.Amask = 0xFF000000,
	.Bmask = 0x00FF0000,
	.Gmask = 0x0000FF00,
	.Rmask = 0x000000FF
};

SDL_Surface *SDL_CreateRGBSurfaceWithFormatFrom(void *pixels, int w, int h, int depth, int pitch, uint32_t format) {
	return NULL;
	// SDL_Surface *surf = SDL_calloc(1, sizeof(SDL_Surface));
	// if (surf) {
	// 	surf->flags = 0;
	// 	surf->format = format == SDL_PIXELFORMAT_ARGB8888 ? &ARGB32 : &ABGR32;
	// 	surf->w = w, surf->h = h;
	// 	surf->pixels = pixels;
	// }
	// if (!surf) nocashMessage("OOM CreateRGBSurfaceWithFormatFrom");
	// return surf;
}
SDL_Surface *SDL_ConvertSurfaceFormat(SDL_Surface *src, uint32_t format, uint32_t flags) {
	return NULL;
	// SDL_Surface *dst = SDL_calloc(1, sizeof(SDL_Surface));
	// if (dst) {
	// 	dst->flags = flags;
	// 	dst->format = format == SDL_PIXELFORMAT_ARGB8888 ? &ARGB32 : &ABGR32;
	// 	dst->w = src->w, dst->h = src->h;
	// 	dst->pixels = malloc(sizeof(src->pixels));
	// 	// TODO: do a conversion I guess
	// 	// uint8_t *srcPx = src->pixels, *dstPx = dst->pixels;
	// 	// for (int i = 0; i < src->w * src->h; i++) {
	// 	// 	uint32_t srcVal = 0;
	// 	// 	for (int b = 0; b < src->format->BytesPerPixel; b++) {
				
	// 	// 	}
	// 	// }
	// 	if (dst->pixels) memcpy(dst->pixels, src->pixels, sizeof(src->pixels));
	// 	else {
	// 		free(dst);
	// 		dst = NULL;
	// 	}
	// }
	// if (!dst) nocashMessage("OOM ConvertSurfaceFormat");
	// return dst;
}

void SDL_FreeSurface(SDL_Surface *surf) {
	/* normally pixels should only be freed if allocated by SDL,
	 * but i think VVVVVV doesn't free the raw pixel data from lodepng anywhere
	 * so we can do it here */
	// SDL_free(surf->pixels);
	// if (surf->format != &ARGB32 && surf->format != &ABGR32) SDL_free(surf->format);
	// SDL_free(surf);
}