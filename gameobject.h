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
    sf::Vector2i coords;
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

#endif // GAMEOBJECT_H
