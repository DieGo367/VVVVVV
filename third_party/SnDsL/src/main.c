#include "SDL.h"

#include <nds/timers.h>
#include <nds/interrupts.h>
#include <nds/arm9/background.h>
#include <nds/bios.h>
#include <nds/debug.h>

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
	// swiWaitForVBlank();
	swiDelay(ms);
}

int SDL_InitSubSystem(uint32_t flags) {
	return 0;
}
void SDL_QuitSubSystem(uint32_t flags) {}

int SDL_Init(uint32_t flags) {
	timerStart(1, ClockDivider_1024, TIMER_FREQ_1024(1000), timerCallback);
	vramSetBankA(VRAM_A_MAIN_BG);
	vramSetBankB(VRAM_B_MAIN_BG_0x06020000);
	videoSetMode(MODE_5_2D);
	bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 8, 0);
	bgInit(3, BgType_ExRotation, BgSize_ER_512x512, 0, 1);
	bgSetCenter(3, 20, 15);
	bgSetScale(3, (5 << 8) / 4, (5 << 8) / 4);
	bgSetScroll(3, 25, 19);
	bgUpdate();
	return 0;
}
void SDL_Quit(void) {}