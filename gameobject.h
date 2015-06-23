#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "renderableobject.h"

class Engine;

class GameObject
{
    friend class Engine;
protected:
    RenderableSprite *queueableObject;
    uint healthPoints;
    uint maxHealthPoints;
    sf::Vector2f coords;
    bool isQueued;
public:
    GameObject(RenderableSprite *p_queueableObject);
    ~GameObject();

    void setHealthPoints(uint points);
    void setMaxHealthPoints(uint points);
    uint getHealthPoints();
    uint getMaxHealthPoints();

    // Defines if this object has to be added to the rendering queue.
    bool isQueueing;
};

enum Direction {
    up,
    upright,
    right,
    downright,
    down,
    downleft,
    left,
    upleft,
    none,
};

#endif // GAMEOBJECT_H
