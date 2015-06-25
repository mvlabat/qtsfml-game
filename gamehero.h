#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <time.h>

#include "gameobject.h"
#include <QDebug>
#include <QElapsedTimer>

class GameHero: public GameObject
{
public:
    bool isMovingUp;
    bool isMovingDown;
    bool isMovingLeft;
    bool isMovingRight;
    Direction direction;
    uint baseSpeed;
    QElapsedTimer timer;
    uint lastTimeMoved;

    GameHero();
    ~GameHero();
    void chooseDirection();
    void move();
protected:
    uint manaPoints;
    uint maxManaPoints;

    void setManaPoints(uint points);
    void setMaxManaPoints(uint points);
    uint getManaPoints();
    uint getMaxManaPoints();
};

#endif // GAMECHARACTER_H
