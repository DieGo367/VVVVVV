#pragma once

typedef struct SDL_Window {} SDL_Window;

typedef enum {
	SDL_WINDOWEVENT_RESIZED,
	SDL_WINDOWEVENT_FOCUS_GAINED,
	SDL_WINDOWEVENT_FOCUS_LOST,
	SDL_WINDOWEVENT_ENTER,
	SDL_WINDOWEVENT_LEAVE,
} SDL_WindowEventID;

typedef struct SDL_DisplayMode {
	int w, h;
} SDL_DisplayMode;
#define SDL_GetDesktopDisplayMode(dispIdx, mode) 0

#define SDL_WINDOW_INPUT_FOCUS 0
#define SDL_WINDOW_FULLSCREEN 0
#define SDL_WINDOW_HIDDEN 0
#define SDL_WINDOW_RESIZABLE 0
#define SDL_WINDOW_ALLOW_HIGHDPI 0
#define SDL_WINDOW_FULLSCREEN_DESKTOP 0
#define SDL_WINDOWPOS_CENTERED_DISPLAY(x) 0
#define SDL_GetWindowFlags(win) 0

#define SDL_CreateWindow(title, x, y, w, h, flags) ((SDL_Window *)1)
#define SDL_GetWindowFromID(id) NULL
#define SDL_GetWindowDisplayIndex(win) 0
#define SDL_ShowWindow(win)
#define SDL_MinimizeWindow(win)
#define SDL_MaximizeWindow(win)
#define SDL_SetWindowTitle(win, title)
#define SDL_SetWindowIcon(win, icon)
#define SDL_SetWindowPosition(win, x, y)
#define SDL_SetWindowSize(win, w, h)
#define SDL_SetWindowMinimumSize(win, w, h)
#define SDL_SetWindowFullscreen(win, flags) 0
#define SDL_DestroyWindow(win)

#define SDL_DisableScreenSaver()
#define SDL_EnableScreenSaver()

#define SDL_GetCurrentVideoDriver() NULL