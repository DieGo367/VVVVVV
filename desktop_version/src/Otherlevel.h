#ifndef OTHERLEVEL_H
#define OTHERLEVEL_H

class otherlevelclass
{
public:
    const unsigned char* loadlevel(int rx, int ry, int* dataLen);

    const char* roomname;
    bool roomname_special;
    const char* hiddenname;

    int roomtileset;
};

#endif /* OTHERLEVEL_H */
