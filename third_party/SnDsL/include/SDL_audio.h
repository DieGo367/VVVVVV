#pragma once
#include "SDL_stdinc.h"
#include "SDL_rwops.h"

typedef uint32_t SDL_AudioDeviceID;

#define AUDIO_F32SYS 0x8120		/**< 32-bit floating point samples */
#define SDL_AUDIO_BITSIZE(x) (x & 0)
typedef uint16_t SDL_AudioFormat;

typedef void (*SDL_AudioCallback) (void *userdata, uint8_t *stream, int len);
typedef struct SDL_AudioSpec {
	int freq;					/**< DSP frequency -- samples per second */
	SDL_AudioFormat format;		/**< Audio data format */
	Uint8 channels;				/**< Number of channels: 1 mono, 2 stereo */
	Uint8 silence;				/**< Audio buffer silence value (calculated) */
	Uint16 samples;				/**< Audio buffer size in sample FRAMES (total samples divided by channel count) */
	Uint16 padding;				/**< Necessary for some compile environments */
	Uint32 size;				/**< Audio buffer size in bytes (calculated) */
	SDL_AudioCallback callback;	/**< Callback that feeds the audio device (NULL to use SDL_QueueAudio()). */
	void *userdata;				/**< Userdata passed to callback (ignored for NULL callbacks). */
} SDL_AudioSpec;

#define SDL_GetNumAudioDrivers() 0
#define SDL_GetAudioDriver(i) NULL

#define SDL_GetNumAudioDevices(isCapture) -1
#define SDL_GetAudioDeviceName(index, isCapture) "N/A"
#define SDL_OpenAudioDevice(device, isCapture, desired, obtained, changesAllowed) 2
#define SDL_PauseAudioDevice(device, pause) {}
#define SDL_CloseAudioDevice(device) {}

int SDL_GetDefaultAudioInfo(char **name, SDL_AudioSpec *spec, int isCapture);
#define SDL_GetAudioDeviceSpec(_index, isCapture, spec) SDL_GetDefaultAudioInfo(NULL, spec, isCapture)

inline SDL_AudioSpec *SDL_LoadWAV_RW(SDL_RWops *src, int freeSrc, SDL_AudioSpec *spec, uint8_t **audioBuf, uint32_t *audioLen) {
	return NULL;
}