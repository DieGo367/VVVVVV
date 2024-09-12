#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <alloca.h>

typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;
typedef uint64_t Uint64;
typedef int8_t Sint8;
typedef int16_t Sint16;
typedef int32_t Sint32;
typedef int64_t Sint64;
typedef enum {
	SDL_FALSE = 0,
	SDL_TRUE = 1
} SDL_bool;

#define SDL_malloc malloc
#define SDL_calloc calloc
#define SDL_realloc realloc
#define SDL_free free

#define SDL_qsort qsort
#define SDL_getenv getenv

#define SDL_atoi atoi
#define SDL_atof atof
#define SDL_strtol strtol
#define SDL_strtoll strtoll

#define SDL_memset memset
#define SDL_memcmp memcmp
#define SDL_memcpy memcpy
#define SDL_memmove memmove

#define SDL_strlen strlen
#define SDL_strchr strchr
#define SDL_strstr strstr
#define SDL_strcmp strcmp
#define SDL_strncmp strncmp
#define SDL_strcasecmp strcasecmp
#define SDL_strdup strdup
#define SDL_strlcpy strlcpy
#define SDL_strlcat strlcat

#define SDL_abs abs
#define SDL_ceil ceil
#define SDL_floor floor
#define SDL_ceilf ceilf
#define SDL_fabsf fabsf
#define SDL_fmodf fmodf

#define SDL_snprintf snprintf
#define SDL_vsnprintf vsnprintf
#define SDL_sscanf sscanf
#define SDL_PRIu64 "llu"
#define SDL_PRIx64 "llx"

#define SDL_isdigit isdigit
#define SDL_isxdigit isxdigit
#define SDL_tolower tolower

#define SDL_min(x, y) (((x) < (y)) ? (x) : (y))
#define SDL_max(x, y) (((x) > (y)) ? (x) : (y))
#define SDL_clamp(x, a, b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

#define SDL_stack_alloc(type, count) (type*)alloca(sizeof(type)*(count))
#define SDL_stack_free(x)

#define SDL_arraysize(array) (sizeof(array)/sizeof(array[0]))

#define SDL_zero(x) SDL_memset(&(x), 0, sizeof((x)))
#define SDL_zerop(x) SDL_memset((x), 0, sizeof(*(x)))
#define SDL_zeroa(x) SDL_memset((x), 0, sizeof((x)))

#define SDL_PRINTF_VARARG_FUNC(argnum)
#define SDL_COMPILE_TIME_ASSERT(name, x) static_assert(x, #x)
#define _SDL_HAS_BUILTIN(x) __has_builtin(x)