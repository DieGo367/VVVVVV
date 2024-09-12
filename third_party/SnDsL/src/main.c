#include "SDL.h"

#include <nds/timers.h>
#include <nds/interrupts.h>
#include <nds/arm9/background.h>
#include <nds/bios.h>
#include <nds/arm9/input.h>
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
	videoSetMode(MODE_5_2D);
	bgInit(2, BgType_Bmp16, BgSize_B16_256x256, 0, 0);
	return 0;
}
void SDL_Quit(void) {}

bool controllerAdded = false, pendingButtons = false;
u32 down = 0, up = 0;
int SDL_PollEvent(SDL_Event *event) {
	if (!controllerAdded) {
		event->cdevice = (SDL_ControllerEvent){
			.type = SDL_CONTROLLERDEVICEADDED
		};
		controllerAdded = true;
		return 1;
	}
	if (!pendingButtons) {
		scanKeys();
		down = keysDown();
		up = keysUp();
		pendingButtons = down || up;
	}
	if (pendingButtons) {
		#define FOR_BUTTONS_DO(DO) \
			DO(START, START); DO(SELECT, GUIDE); \
			DO(A, B); DO(B, A); DO(X, Y); DO(Y, X); \
			DO(L, LEFTSHOULDER); DO(R, RIGHTSHOULDER); \
			DO(UP, DPAD_UP); DO(DOWN, DPAD_DOWN); DO(LEFT, DPAD_LEFT); DO(RIGHT, DPAD_RIGHT);
		#define CHECK_MASK(mask, EVENT, NDS, SDL) \
			if (mask & KEY_##NDS) { \
				mask ^= KEY_##NDS; \
				event->cbutton = (SDL_ControllerEvent){ \
					.type = SDL_CONTROLLERBUTTON##EVENT, \
					.button = SDL_CONTROLLER_BUTTON_##SDL \
				}; \
				return 1; \
			}
		#define CHECK_DOWN(NDS, SDL) CHECK_MASK(down, DOWN, NDS, SDL)
		#define CHECK_UP(NDS, SDL) CHECK_MASK(up, UP, NDS, SDL)

		FOR_BUTTONS_DO(CHECK_DOWN)
		FOR_BUTTONS_DO(CHECK_UP)

		pendingButtons = false;
	}

	return 0;
}