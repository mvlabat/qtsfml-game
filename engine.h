#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>
#include <QDebug>
#include <QTime>
#include <QPushButton>
#include <QKeyEvent>

#include "gamesettings.h"
#include "controls.h"
#include "level.h"
#include "gamedata.h"
#include "renderableobject.h"
#include "binarysearchtree.h"
#include "fonts.h"

class QSFMLCanvas;

class Engine: public QObject
{
    Q_OBJECT

    friend class QSFMLCanvas;
protected:
    // Reference to the main (parent) widget for drawing.
    sf::RenderTarget *renderTarget;
    // Class which manages game settings.
    GameSettings *settings;
    // Class which manages game controls.
    Controls controls;
    // BST which is used for ordering renderable objects by z-index.
    BinarySearchTree<RenderableObject *> tree;
    // Class which manages all the game (current level) data.
    GameData *gameData;
    // Class which manages loading a level.
    Level level;
    // Text for rendering fps count.
    RenderableText fpsText;
    // FPS counter.
    int frames;
    // Variable which stores system time of last fps output.
    QTime fpsTimer;

    void processGameData();
    void processPressedKeyEvent(QKeyEvent *);
    void processReleasedKeyEvent(QKeyEvent *);
    void render();
public:
    Engine(sf::RenderTarget *p_renderTarget, GameSettings *p_settings);
    ~Engine();
    static bool compare(RenderableObject *x, RenderableObject *y);
    void addToRenderQueue(RenderableObject *object);
    void deleteFromRenderQueue(RenderableObject *object);

protected slots:
    void countFps();
};

#endif // ENGINE_H
