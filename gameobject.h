#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "renderableobject.h"

class Engine;

class GameObject
{
    friend class Engine;
protected:
    RenderableSprite *renderableObject;
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
    Up,
    UpRight,
    Right,
    DownRight,
    Down,
    DownLeft,
    Left,
    UpLeft,
    None,
};

#endif // GAMEOBJECT_H
