#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include "gameobject.h"

class GameHero: public GameObject
{
public:
    GameHero();
    ~GameHero();

protected:
    uint manaPoints;
    uint maxManaPoints;

    void setManaPoints(uint points);
    void setMaxManaPoints(uint points);
    uint getManaPoints();
    uint getMaxManaPoints();
};

#endif // GAMECHARACTER_H
