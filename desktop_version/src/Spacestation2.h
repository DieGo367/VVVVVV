#ifndef SPACESTATION2_H
#define SPACESTATION2_H

class spacestation2class
{
public:
    const unsigned char* loadlevel(int rx, int ry, int* dataLen);
    const char* roomname;
    bool roomname_special;
};

#endif /* SPACESTATION2_H */
