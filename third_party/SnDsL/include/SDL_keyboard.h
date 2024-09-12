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
	SDLK_0, SDLK_1, SDLK_2, SDLK_3, SDLK_4, SDLK_5, SDLK_6, SDLK_7, SDLK_8, SDLK_9,
	SDLK_r, SDLK_t, SDLK_y, SDLK_u, SDLK_i, SDLK_o, SDLK_p,
	SDLK_LSHIFT, SDLK_RSHIFT,
	SDLK_F1, SDLK_F2, SDLK_F3, SDLK_F4, SDLK_F5, SDLK_F6, SDLK_F8, SDLK_F9, SDLK_F10, SDLK_F11,
	SDLK_g, SDLK_l, SDLK_f, SDLK_h, SDLK_b, SDLK_c, SDLK_x,
	SDLK_COMMA, SDLK_LCTRL, SDLK_RCTRL, SDLK_PERIOD,
	SDLK_KP_ENTER,
	SDLK_LALT, SDLK_RALT,
	SDLK_TAB,
	SDLK_ESCAPE
} SDL_KeyCode;

// mouse.h

#define SDL_BUTTON_LEFT		1
#define SDL_BUTTON_MIDDLE	2
#define SDL_BUTTON_RIGHT	3
#define SDL_ShowCursor(toggle) SDL_DISABLE

// clipboard.h

#define SDL_GetClipboardText() ""
#define SDL_SetClipboardText(text) 0