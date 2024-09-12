#include "SDL.h"

#include <nds/arm9/console.h>
#include <nds/arm9/input.h>
#include <nds/interrupts.h>

int SDL_ShowSimpleMessageBox(uint32_t flags, const char *title, const char *message, SDL_Window *window) {
	if (flags & SDL_MESSAGEBOX_ERROR) {
		printf("\x1b[31;1m");
	}
	
	printf(    " ------------------------------ ");
	for (int i = 0; i < 22; i++)
		printf("|                              |");
	printf(    " ------------------- (A) OK ---");

	int titlePos = (32 - (strlen(title) + 2)) / 2;
	if (titlePos < 0) titlePos = 0;
	PrintConsole *c = consoleSelect(NULL);
	consoleSelect(c);
	c->cursorX = titlePos;
	c->cursorY = 0;
	printf(" %.31s ", title);
	
	consoleSetWindow(NULL, 2, 2, 28, 20);
	consoleClear();
	printf(message);

	while (true) {
		swiWaitForVBlank();
		scanKeys();
		if (keysDown() & (KEY_A)) break;
	}

	printf("\x1b[0m");
	consoleSetWindow(NULL, 0, 0, 32, 24);
	consoleClear();

	return 0;
}