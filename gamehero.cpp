#include "gamehero.h"

GameHero::GameHero() :
    GameObject(new RenderableSprite(ZIndexes::Hero)),
    isMovingUp(false),
    isMovingDown(false),
    isMovingLeft(false),
    isMovingRight(false),
    direction(Direction::None),
    baseSpeed(800),
    lastTimeMoved(0),
    name(ZIndexes::GameObjectFloatingText)
{
    timer.start();
    renderableObject->setTexture("molfar.png");
    name.parentObject = renderableObject;
    name.text.setString("mvlabat");
}

GameHero::~GameHero()
{

}

void GameHero::chooseDirection()
{
    direction = Direction::None;
    if (isMovingUp && !isMovingDown)
    {
        direction = Direction::Up;
    }
    else if (isMovingDown && !isMovingUp)
    {
        direction = Direction::Down;
    }
    if (isMovingRight && !isMovingLeft)
    {
        if (direction == Direction::None)
        {
            direction = Direction::Right;
        }
        else
        {
            direction = (direction == Direction::Up) ? Direction::UpRight : Direction::DownRight;
        }
    }
    else if (isMovingLeft && !isMovingRight)
    {
        if (direction == Direction::None)
        {
            direction = Direction::Left;
        }
        else
        {
            direction = (direction == Direction::Up) ? Direction::UpLeft : Direction::DownLeft;
        }
    }
}

void GameHero::move()
{
    uint milliseconds;
    float length;
    float diagonalLength;

    chooseDirection();

    milliseconds = timer.elapsed() - lastTimeMoved;
    lastTimeMoved = timer.elapsed();
    length = (float)baseSpeed * milliseconds / 10000;
    diagonalLength = length / sqrt(2);

    switch (direction)
    {
    case Direction::Up:
        coords.y -= length;
        break;
    case Direction::UpRight:
        coords.y -= diagonalLength;
        coords.x += diagonalLength;
        break;
    case Direction::Right:
        coords.x += length;
        break;
    case Direction::DownRight:
        coords.y += diagonalLength;
        coords.x += diagonalLength;
        break;
    case Direction::Down:
        coords.y += length;
        break;
    case Direction::DownLeft:
        coords.y += diagonalLength;
        coords.x -= diagonalLength;
        break;
    case Direction::Left:
        coords.x -= length;
        break;
    case Direction::UpLeft:
        coords.y -= diagonalLength;
        coords.x -= diagonalLength;
        break;
    default:
        lastTimeMoved = 0;
        timer.restart();
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

uint GameHero::getManaPoints() const
{
    return manaPoints;
}

uint GameHero::getMaxManaPoints() const
{
    return maxManaPoints;
}

