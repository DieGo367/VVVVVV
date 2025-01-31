#include "SDL.h"

#include <nds/timers.h>
#include <nds/bios.h>

uint64_t ticks = 0;
void timerCallback() {
	ticks++;
}
uint32_t SDL_GetTicks(void) {
	return ticks;
}
uint64_t SDL_GetTicks64(void) {
	return ticks;
}

void SDL_Delay(uint32_t ms) {
	swiDelay(ms);
}

int SDL_InitSubSystem(uint32_t flags) {
	return 0;
}
void SDL_QuitSubSystem(uint32_t flags) {}

int SDL_Init(uint32_t flags) {
	timerStart(1, ClockDivider_1024, TIMER_FREQ_1024(1000), timerCallback);
	return 0;
}
void SDL_Quit(void) {}