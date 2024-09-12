#ifndef WARPCLASS_H
#define WARPCLASS_H

class warpclass
{
public:
    const unsigned char* loadlevel(int rx, int ry, int* dataLen);
    const char* roomname;
    bool roomname_special;
    int rcol;
    bool warpx, warpy;
};

#endif /* WARPCLASS_H */
