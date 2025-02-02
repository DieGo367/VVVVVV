#ifndef ROOMNAMETRANSLATOR_H
#define ROOMNAMETRANSLATOR_H

#include <SDL.h>

namespace roomname_translator
{
    extern bool enabled;
    extern bool edit_mode;

    #ifndef __NDS__
    extern SDL_Surface* dimbuffer;
    #endif
    extern SDL_Rect fullscreen_rect;

    void set_enabled(bool value);
    bool is_pausing(void);
    void overlay_render(bool* force_roomname_hidden, bool* roomname_untranslated, int* roomname_r, int* roomname_g, int* roomname_b);
    bool overlay_input(void);
}

#endif /* ROOMNAMETRANSLATOR_H */
