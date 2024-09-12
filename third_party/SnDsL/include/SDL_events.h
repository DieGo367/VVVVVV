#pragma once
#include "SDL_gamecontroller.h"
#include "SDL_keyboard.h"

#define SDL_QUERY   -1
#define SDL_DISABLE  0
#define SDL_ENABLE   1

typedef struct SDL_KeyboardEvent {
	uint32_t type;
	struct {
		SDL_Keycode sym;
	} keysym;
	uint8_t repeat;
} SDL_KeyboardEvent;
typedef struct SDL_TextInputEvent {
	uint32_t type;
	char text[4];
} SDL_TextInputEvent;
typedef struct SDL_TextEditEvent {
	uint32_t type;
	char text[4];
	int start, length;
} SDL_TextEditEvent;
typedef struct SDL_MouseEvent {
	uint32_t type;
	int32_t x, y;
	uint8_t button;
} SDL_MouseEvent;
typedef struct SDL_ControllerEvent {
	uint32_t type;
	SDL_JoystickID which;
	uint8_t button;
	uint8_t axis;
	int16_t value;
} SDL_ControllerEvent;
typedef struct SDL_WindowEvent {
	uint32_t type;
	uint8_t event;
} SDL_WindowEvent;
typedef union SDL_Event {
	uint32_t type;
	SDL_KeyboardEvent key;
	SDL_TextInputEvent text;
	SDL_TextEditEvent edit, editExt;
	SDL_MouseEvent motion, button;
	SDL_ControllerEvent cbutton, caxis, cdevice;
	SDL_WindowEvent window;
} SDL_Event;

typedef enum {
	SDL_KEYDOWN, SDL_KEYUP,
	SDL_TEXTINPUT,
	SDL_TEXTEDITING,
	SDL_TEXTEDITING_EXT,
	SDL_MOUSEMOTION,
	SDL_MOUSEBUTTONDOWN,
	SDL_MOUSEBUTTONUP,
	SDL_CONTROLLERBUTTONDOWN,
	SDL_CONTROLLERBUTTONUP,
	SDL_CONTROLLERAXISMOTION,
	SDL_CONTROLLERDEVICEADDED,
	SDL_CONTROLLERDEVICEREMOVED,
	SDL_WINDOWEVENT,
	SDL_QUIT
} SDL_EventType;

int SDL_PollEvent(SDL_Event *event);