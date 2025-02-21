#ifndef TOWERBG_H
#define TOWERBG_H

#include <SDL.h>

struct TowerBG
{
    #ifndef __NDS__
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
