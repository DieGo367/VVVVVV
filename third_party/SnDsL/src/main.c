#include <nds/timers.h>
#include <nds/bios.h>
#include <ndsabi.h>

// Assumes 2-byte aligned. @param count number of u16 to write
void memset16(uint16_t *dst, uint16_t src, size_t count) {
	uint32_t word = src << 16 | src;
	uint32_t misaligned = (uint32_t) dst & 3;
	if (misaligned) dst++[0] = src;
	__ndsabi_wordset4(dst, (count * 2) - misaligned, word);
}

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

void initTimer(void) {
	timerStart(1, ClockDivider_1024, TIMER_FREQ_1024(1000), timerCallback);
}