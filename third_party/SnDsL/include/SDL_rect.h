#pragma once
#include "SDL_stdinc.h"

typedef struct SDL_Point {
	int x, y;
} SDL_Point;
typedef struct SDL_Rect {
	int x, y;
	int w, h;
} SDL_Rect;

inline SDL_bool SDL_PointInRect(const SDL_Point *p, const SDL_Rect *r) {
	return ( (p->x >= r->x) && (p->x < (r->x + r->w)) &&
			 (p->y >= r->y) && (p->y < (r->y + r->h)) ) ? SDL_TRUE : SDL_FALSE;
}

inline SDL_bool SDL_HasIntersection(const SDL_Rect *A, const SDL_Rect *B) {
	return SDL_FALSE;
}