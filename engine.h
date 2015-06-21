#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>
#include <QDebug>
#include <QTimer>
#include <QPushButton>

#include "gamesettings.h"
#include "level.h"
#include "gamedata.h"
#include "renderableobject.h"
#include "binarysearchtree.h"

class QSFMLCanvas;

class Engine: public QObject
{
    Q_OBJECT

    friend class QSFMLCanvas;
protected:
    sf::RenderTarget *renderTarget;
    GameSettings *settings;
    BinarySearchTree<QueueableObject *> tree;
    GameData *gameData;
    Level *level;
    sf::Font font;
    RenderableText *fpsText;
    int frames;
    QTimer *fpsTimer;
    QPushButton *button;

    void parseGameData();
    void render();
public:
    Engine(sf::RenderTarget *p_renderTarget, GameSettings *p_settings);
    ~Engine();
    static bool compare(QueueableObject *x, QueueableObject *y);
    void addToRenderQueue(QueueableObject *object);
    void deleteFromRenderQueue(QueueableObject *object);

protected slots:
    void countFps();
};

#endif // ENGINE_H
