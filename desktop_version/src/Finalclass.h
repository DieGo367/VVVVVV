#ifndef FINALCLASS_H
#define FINALCLASS_H

class finalclass
{
public:
    const unsigned char* loadlevel(int rx, int ry, int* dataLen);

    const char* roomname;
    bool roomname_special;
    bool warpx, warpy;
};

#endif /* FINALCLASS_H */
