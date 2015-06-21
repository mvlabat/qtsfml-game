#ifndef LEVEL_H
#define LEVEL_H

#include "gamedata.h"

class Level
{
protected:
    GameData *gameData;
public:
    Level(GameData *p_gameData);
};

#endif // LEVEL_H
