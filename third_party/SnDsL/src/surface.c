#include "SDL_surface.h"

SDL_Surface *SDL_CreateRGBSurface(uint32_t flags, int w, int h, int depth, uint32_t rmask, uint32_t gmask, uint32_t bmask, uint32_t amask) {
	return NULL;
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
}
SDL_Surface *SDL_ConvertSurfaceFormat(SDL_Surface *src, uint32_t format, uint32_t flags) {
	return NULL;
}

void SDL_FreeSurface(SDL_Surface *surf) {
}