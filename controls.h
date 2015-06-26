#ifndef CONTROLS_H
#define CONTROLS_H

#include <QKeyEvent>
#include <QKeySequence>

#include <gamehero.h>

class Engine;

class Controls
{
    friend class Engine;
protected:
    GameHero *hero;

    void processPressedHeroControls(QKeyEvent *event);
    void processReleasedHeroControls(QKeyEvent *event);
public:
    Controls();
    void setControlledHero(GameHero *p_hero);
};

#endif // CONTROLS_H
