#pragma once
#include <stdint.h>

#define SDL_StartTextInput()
#define SDL_StopTextInput()
#define SDL_IsTextInputActive() SDL_FALSE
#define SDL_SetTextInputRect(rect)

// keycode.h

typedef int32_t SDL_Keycode;
typedef enum {
	SDLK_UNKNOWN = 0,
	SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_RETURN, SDLK_SPACE,
	SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_e, SDLK_m, SDLK_n, SDLK_v, SDLK_z,
	SDLK_BACKSPACE,
	SDLK_r, SDLK_y, SDLK_u, SDLK_i,
	SDLK_LSHIFT, SDLK_RSHIFT,
	SDLK_F1,
	SDLK_f,
	SDLK_LCTRL, SDLK_RCTRL, SDLK_PERIOD,
	SDLK_KP_ENTER,
	SDLK_TAB,
	SDLK_ESCAPE
} SDL_KeyCode;

// clipboard.h

#define SDL_GetClipboardText() ""
#define SDL_SetClipboardText(text) 0