#include "SDL_audio.h"

int SDL_GetDefaultAudioInfo(char **name, SDL_AudioSpec *spec, int isCapture) {
	*name = NULL;
	spec->freq = 48000;
	spec->channels = 2;
	return 1;
}