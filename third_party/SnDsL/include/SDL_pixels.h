#pragma once
#include "SDL_stdinc.h"

typedef struct SDL_Color
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} SDL_Color;
#define SDL_Colour SDL_Color
typedef struct SDL_PixelFormat
{
	Uint8 BitsPerPixel;
	Uint8 BytesPerPixel;
	Uint32 Rmask;
	Uint32 Gmask;
	Uint32 Bmask;
	Uint32 Amask;
} SDL_PixelFormat;

#define SDL_PIXELFORMAT_ARGB8888 1
#define SDL_PIXELFORMAT_ABGR8888 2

inline uint32_t SDL_MapRGB(const SDL_PixelFormat *format, uint32_t r, uint32_t g, uint32_t b) {
	return 0;
}
inline uint32_t SDL_MapRGBA(const SDL_PixelFormat *format, uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
	return 0;
}

#define SDL_GetRGB(pixel, format, r, g, b)
#define SDL_GetRGBA(pixel, format, r, g, b, a)