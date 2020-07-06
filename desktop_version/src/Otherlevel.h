#ifndef OTHERLEVEL_H
#define OTHERLEVEL_H

#include "Game.h"
#include "Entity.h"

#include <string>
#include <vector>

struct Roomtext
{
    int x, y;
    std::string text;
};

class otherlevelclass
{
public:
    enum
    {
        BLOCK = 0,
        TRIGGER,
        DAMAGE,
        DIRECTIONAL,
        SAFE,
        ACTIVITY
    };

    const int* loadlevel(int rx, int ry);

    std::string roomname;

    int roomtileset;
};

#endif /* OTHERLEVEL_H */
