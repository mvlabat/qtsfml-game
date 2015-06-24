#include "gameobject.h"

GameObject::GameObject(RenderableSprite *p_queueableObject) :
    queueableObject(p_queueableObject),
    coords(sf::Vector2f(0, 0)),
    isQueued(false),
    isQueueing(true)
{
}

GameObject::~GameObject()
{
    delete queueableObject;
}

void GameObject::setHealthPoints(uint points)
{
    if (points < maxHealthPoints)
    {
        healthPoints = points;
    }
    else
    {
        healthPoints = maxHealthPoints;
    }
}

void GameObject::setMaxHealthPoints(uint points)
{
    maxHealthPoints = points;
}

uint GameObject::getHealthPoints()
{
    return healthPoints;
}

uint GameObject::getMaxHealthPoints()
{
    return maxHealthPoints;
}

