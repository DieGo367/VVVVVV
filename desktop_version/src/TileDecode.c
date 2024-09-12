#include <stddef.h>
#include <SDL_assert.h>

// Decode tiles to the destination pointer. Warning: Assumes destination has enough space.
void decodeTilesShort(short *dest, const unsigned char *data, size_t dataLen) {
	short tile = 0, run;
	for (size_t i = 0; i < dataLen; i++) {
		unsigned char byte = data[i];
		switch (byte & 0xC0) {
		case 0xC0:
			run = byte & 0x3F;
			if (i+1 < dataLen && (data[i+1] & 0xC0) == 0xC0) {
				run |= (data[++i] & 0x3F) << 6;
			}
			while (run--) *dest++ = tile;
			break;
		case 0x80:
			SDL_assert(++i < dataLen);
			tile = (byte & 0x3F) | (data[i] << 6);
			*dest++ = tile;
			break;
		default:
			tile = byte;
			*dest++ = tile;
			break;
		}
	}
}

// Decode tiles to the destination pointer. Warning: Assumes destination has enough space.
void decodeTilesInt(int *dest, const unsigned char *data, size_t dataLen) {
	short tile = 0, run;
	for (size_t i = 0; i < dataLen; i++) {
		unsigned char byte = data[i];
		switch (byte & 0xC0) {
		case 0xC0:
			run = byte & 0x3F;
			if (i+1 < dataLen && (data[i+1] & 0xC0) == 0xC0) {
				run |= (data[++i] & 0x3F) << 6;
			}
			while (run--) *dest++ = tile;
			break;
		case 0x80:
			SDL_assert(++i < dataLen);
			tile = (byte & 0x3F) | (data[i] << 6);
			*dest++ = tile;
			break;
		default:
			tile = byte;
			*dest++ = tile;
			break;
		}
	}
}