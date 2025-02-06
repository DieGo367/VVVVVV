#pragma once
#include <stdint.h>

void SDL_Delay(uint32_t ms);
void initTimer(void);
uint32_t SDL_GetTicks(void);
uint64_t SDL_GetTicks64(void);