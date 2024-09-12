#ifndef TILEDECODE_H
#define TILEDECODE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stddef.h>

void decodeTilesShort(short *dest, const unsigned char *data, size_t dataLen);
void decodeTilesInt(int *dest, const unsigned char *data, size_t dataLen);

#ifdef __cplusplus
}
#endif

#endif /* TILEDECODE_H */
