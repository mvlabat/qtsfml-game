#include "gameobject.h"

GameObject::GameObject(RenderableSprite *p_queueableObject) :
    renderableObject(p_queueableObject),
    coords(sf::Vector2f(0, 0)),
    isQueued(false),
    isQueueing(true)
{
}

GameObject::~GameObject()
{
    delete renderableObject;
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

uint GameObject::getHealthPoints() const
{
    return healthPoints;
}

uint GameObject::getMaxHealthPoints() const
{
    return maxHealthPoints;
}

