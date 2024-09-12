/*
	SnDsL - A shim-like library implementing a minimal portion of SDL2 on NDS

	Function signatures, macros, and header names referenced from SDL2 2.30.4 headers
	https://github.com/libsdl-org/SDL/tree/SDL2
*/

#ifndef SDL_h_
#define SDL_h_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>

#include "SDL_stdinc.h"
#include "SDL_assert.h"
#include "SDL_audio.h"
#include "SDL_endian.h"
#include "SDL_events.h"
#include "SDL_log.h"
#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_rwops.h"
#include "SDL_surface.h"
#include "SDL_timer.h"
#include "SDL_video.h"


#define SDL_INIT_AUDIO			0b1
#define SDL_INIT_VIDEO			0b10
#define SDL_INIT_JOYSTICK		0
#define SDL_INIT_GAMECONTROLLER	0

int SDL_InitSubSystem(uint32_t flags);
void SDL_QuitSubSystem(uint32_t flags);

int SDL_Init(uint32_t flags);
void SDL_Quit(void);

// version.h

#define SDL_MAJOR_VERSION	2
#define SDL_MINOR_VERSION	30
#define SDL_PATCHLEVEL		4

#define SDL_VERSION_ATLEAST(major, minor, patch) ( \
	(SDL_MAJOR_VERSION > major) || \
	(SDL_MAJOR_VERSION == major && SDL_MINOR_VERSION > minor) || \
	(SDL_MAJOR_VERSION == major && SDL_MINOR_VERSION == minor && SDL_PATCHLEVEL >= patch) \
)

// begin_code.h

#define SDLCALL
#define SDL_INLINE inline
#define SDL_FORCE_INLINE __attribute__((always_inline)) static inline
#define SDL_NORETURN __attribute__((noreturn))
#define SDL_FALLTHROUGH __attribute__((__fallthrough__))

// error.h

#define SDL_GetError() "SnDsL errs are currently unimplemented sry"
#define SDL_SetError(...)

// filesystem.h & misc.h

#include <fat.h>
#define SDL_GetBasePath fatGetDefaultCwd
inline int SDL_OpenURL(const char *url) {
	return -1;
}

// platform.h

#define SDL_GetPlatform() "NintendoDS"

// hints.h

#define SDL_GetHint(name) NULL
#define SDL_SetHint(name, value) false
#define SDL_GetHintBoolean(name, fallback) fallback
#define SDL_SetHintWithPriority(name, value, priority)
#define SDL_HINT_RENDER_DRIVER ""

// cpuinfo.h

#define SDL_HasSSE2() false
#define SDL_HasNEON() false

// loadso.h

#define SDL_LoadObject(x) NULL
#define SDL_UnloadObject(x)
#define SDL_LoadFunction(dll, x) NULL

// thread.h

typedef int (*SDL_ThreadFunction) (void *data);
typedef struct SDL_Thread {} SDL_Thread;
#define SDL_CreateThread(func, name, data) NULL
#define SDL_WaitThread(thread, status)
#define SDL_SetThreadPriority(priority) 0
typedef unsigned long SDL_threadID;
#define SDL_ThreadID() 0

// mutex.h

typedef struct SDL_mutex {} SDL_mutex;
#define SDL_CreateMutex() NULL
#define SDL_DestroyMutex(mutex)
#define SDL_LockMutex(mutex) 0
#define SDL_UnlockMutex(mutex) 0

// messagebox.h

typedef enum {
	SDL_MESSAGEBOX_ERROR = 1,
} SDL_MessageBoxFlags;

int SDL_ShowSimpleMessageBox(uint32_t flags, const char *title, const char *message, SDL_Window *window);

#ifdef __cplusplus
}
#endif

#endif /* SDL_h_ */