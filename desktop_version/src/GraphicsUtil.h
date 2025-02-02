#ifndef GRAPHICSUTIL_H
#define GRAPHICSUTIL_H

#include <SDL.h>

#ifdef __NDS__
#define VRAM_COLOR(r, g, b) (1 << 15 | ((b) >> 3) << 10 | ((g) >> 3) << 5 | (r) >> 3)
#define RENDER_SCALE(x) (((x)*4 + 3)/5)
#endif

void setRect(SDL_Rect& _r, int x, int y, int w, int h);

#ifndef __NDS__
SDL_Surface* GetSubSurface( SDL_Surface* metaSurface, int x, int y, int width, int height );

void DrawPixel(SDL_Surface* surface, int x, int y, SDL_Color color);

SDL_Color ReadPixel(const SDL_Surface* surface, int x, int y);
#endif

void UpdateFilter(void);
#ifndef __NDS__
void ApplyFilter(SDL_Surface** src, SDL_Surface** dest);

bool TakeScreenshot(SDL_Surface** surface);
bool UpscaleScreenshot2x(SDL_Surface* src, SDL_Surface** dest);
#endif

#endif /* GRAPHICSUTIL_H */
