#include "gamehero.h"

GameHero::GameHero() :
    GameObject(new RenderableSprite(zIndexes::hero)),
    isMovingUp(false),
    isMovingDown(false),
    isMovingLeft(false),
    isMovingRight(false),
    direction(Direction::none),
    baseSpeed(40),
    lastTimeMoved(QTime::currentTime())
{
    RenderableSprite *renderableHero = (RenderableSprite *)queueableObject;
    renderableHero->texture.loadFromFile("molfar.png");
    renderableHero->setTexture(renderableHero->texture);
}

GameHero::~GameHero()
{

}

void GameHero::chooseDirection()
{
    direction = Direction::none;
    if (isMovingUp && !isMovingDown)
    {
        direction = Direction::up;
    }
    else if (isMovingDown && !isMovingUp)
    {
        direction = Direction::down;
    }
    if (isMovingRight && !isMovingLeft)
    {
        if (direction == Direction::none)
        {
            direction = Direction::right;
        }
        else
        {
            direction = (direction == Direction::up) ? Direction::upright : Direction::downright;
        }
    }
    else if (isMovingLeft && !isMovingRight)
    {
        if (direction == Direction::none)
        {
            direction = Direction::left;
        }
        else
        {
            direction = (direction == Direction::up) ? Direction::upleft : Direction::downleft;
        }
    }
}

void GameHero::move()
{
    uint milliseconds;
    float length;

    milliseconds = (lastTimeMoved - QTime::currentTime()).msec();
    lastTimeMoved = QTime::currentTime();
    length = baseSpeed * 100 / milliseconds;
    diagonalLength = length / sqrt(2);

    switch (direction)
    {
    case Direction::up:
        coords.y -= length;
        break;
    case Direction::upright:
        coords.y -= diagonalLength;
        coords.x += diagonalLength;
        break;
    case Direction::right:
        coords.x += length;
        break;
    case Direction::downright:
        coords.y += diagonalLength;
        coords.x -= diagonalLength;
        break;
    case Direction::down:
        coords.y += length;
        break;
    case Direction::downleft:
        coords.y += diagonalLength;
        coords.x -= diagonalLength;
        break;
    case Direction::left:
        coords.x -= length;
        break;
    case Direction::upleft:
        coords.y -= diagonalLength;
        coords.x -= diagonalLength;
        break;
    }
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

