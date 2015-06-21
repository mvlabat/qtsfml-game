#include "gamehero.h"

GameHero::GameHero() :
    GameObject(new RenderableSprite(zIndexes::hero))
{
    RenderableSprite *renderableHero = (RenderableSprite *)queueableObject;
    renderableHero->texture.loadFromFile("molfar.png");
    renderableHero->setTexture(renderableHero->texture);
}

GameHero::~GameHero()
{

}

void GameHero::setManaPoints(uint points)
{
    if (points < maxManaPoints)
    {
        manaPoints = points;
    }
    else
    {
        manaPoints = maxManaPoints;
    }
}

void GameHero::setMaxManaPoints(uint points)
{
    maxManaPoints = points;
}

uint GameHero::getManaPoints()
{
    return manaPoints;
}

uint GameHero::getMaxManaPoints()
{
    return maxManaPoints;
}

