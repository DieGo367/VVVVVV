#ifndef LABCLASS_H
#define LABCLASS_H

class labclass
{
public:
    const unsigned char* loadlevel(int rx, int ry, int* dataLen);

    const char* roomname;
    bool roomname_special;
    int rcol;
};
#endif /* LABCLASS_H */
