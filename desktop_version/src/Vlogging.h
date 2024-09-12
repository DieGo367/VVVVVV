#ifndef VLOGGING_H
#define VLOGGING_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <SDL_stdinc.h>

void vlog_init(void);

#ifdef _WIN32
void vlog_open_console(void);
#endif

#ifdef __NDS__
#include <nds/debug.h>
#define nocashf(fmt, ...) do { \
	char message[120]; \
	int amt = snprintf(message, 120, fmt, __VA_ARGS__); \
	nocashWrite(message, amt); \
} while(0)
#endif

void vlog_toggle_output(int enable_output);

void vlog_toggle_color(int enable_color);

void vlog_toggle_debug(int enable_debug);

void vlog_toggle_info(int enable_info);

void vlog_toggle_warn(int enable_warn);

void vlog_toggle_error(int enable_error);

SDL_PRINTF_VARARG_FUNC(1) void vlog_debug(const char* text, ...);

SDL_PRINTF_VARARG_FUNC(1) void vlog_info(const char* text, ...);

SDL_PRINTF_VARARG_FUNC(1) void vlog_warn(const char* text, ...);

SDL_PRINTF_VARARG_FUNC(1) void vlog_error(const char* text, ...);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* VLOGGING_H */
