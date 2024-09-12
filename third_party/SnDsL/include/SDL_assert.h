#pragma once
#include <nds/arm9/sassert.h>
// #include <assert.h>

// inline void SDL_assert(unsigned char condition) { // needed when assert is redefined
// 	sassert(condition, "Assertion failed!");
// }
#define SDL_assert(condition) sassert(condition, "")