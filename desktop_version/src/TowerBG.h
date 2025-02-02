#ifndef TOWERBG_H
#define TOWERBG_H

#include <SDL.h>
#ifdef __NDS__
#include "GraphicsResources.h"
#endif

struct TowerBG
{
    #ifdef __NDS__
    Bitmap* texture;
    #else
    SDL_Texture* texture;
    #endif
    bool tdrawback;
    int bypos;
    int bscroll;
    int colstate;
    int scrolldir;
    int r;
    int g;
    int b;
};

#endif /* TOWERBG_H */
