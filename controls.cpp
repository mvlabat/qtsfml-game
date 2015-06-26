#include "controls.h"

void Controls::processPressedHeroControls(QKeyEvent *event)
{
    qDebug() << event->key() << event->nativeScanCode() << event->nativeVirtualKey();
    switch (event->key())
    {
        case Qt::Key_W:
            hero->isMovingUp = true;
            hero->isMovingDown = false;
        break;
        case Qt::Key_S:
            hero->isMovingDown = true;
            hero->isMovingUp = false;
        break;
        case Qt::Key_A:
            hero->isMovingLeft = true;
            hero->isMovingRight = false;
        break;
        case Qt::Key_D:
            hero->isMovingRight = true;
            hero->isMovingLeft = false;
        break;
    }
}

void Controls::processReleasedHeroControls(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_W:
            hero->isMovingUp = false;
        break;
        case Qt::Key_S:
            hero->isMovingDown = false;
        break;
        case Qt::Key_A:
            hero->isMovingLeft = false;
        break;
        case Qt::Key_D:
            hero->isMovingRight = false;
        break;
    }
}

Controls::Controls()
{

}

void Controls::setControlledHero(GameHero *p_hero)
{
    hero = p_hero;
}

