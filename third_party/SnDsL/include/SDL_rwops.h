#pragma once
#include "SDL_stdinc.h"
#include <stdio.h>

#define RW_SEEK_SET 0
#define RW_SEEK_CUR 1
#define RW_SEEK_END 2

#define SDL_RWOPS_MEMORY 1 // idc
typedef struct SDL_RWops {
	Sint64 (*size) (struct SDL_RWops *self); // Filesize. -1 = unknown
	Sint64 (*seek) (struct SDL_RWops *self, Sint64 offset, int whence); // Returns final offset. -1 = error
	size_t (*read) (struct SDL_RWops *self, void *ptr, size_t size, size_t maxnum); // Returns bytes read. 0 = error or EOF
	size_t (*write) (struct SDL_RWops *self, const void *ptr, size_t size, size_t num); // Returns bytes written. 0 = error or EOF
	int (*close) (struct SDL_RWops *self); // 0 = success, -1 = error.
	Uint32 type;
	union {
		FILE *file;
		struct {
			Uint8 *base;
		} mem;
		struct {
			void *data1;
		} unknown;
	} hidden;

} SDL_RWops;

#define SDL_AllocRW(rw) NULL
#define SDL_FreeRW(rw)

inline SDL_RWops *SDL_RWFromFile(const char *file, const char *mode) {
	return NULL;
}
inline SDL_RWops *SDL_RWFromMem(void *mem, int size) {
	return NULL;
}
inline SDL_RWops *SDL_RWFromConstMem(const void *mem, int size) {
	return NULL;
}

#define SDL_RWread(rw, buf, count, sz)
#define SDL_RWclose(rw)
