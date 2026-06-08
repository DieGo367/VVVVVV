#ifndef OTHERLEVEL_H
#define OTHERLEVEL_H

#ifdef __NDS__
#include "LocalizationIDs.h"
#endif

class otherlevelclass
{
public:
    const unsigned char* loadlevel(int rx, int ry, int* dataLen);

    const char* roomname;
    bool roomname_special;
    #ifdef __NDS__
    Special_Roomname_String_ID hiddenname;
    #else
    const char* hiddenname;
    #endif

    int roomtileset;
};

#endif /* OTHERLEVEL_H */
