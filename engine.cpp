#include "engine.h"

Engine::Engine(sf::RenderTarget *p_renderTarget, GameSettings *p_settings) :
    QObject(),
    renderTarget(p_renderTarget),
    settings(p_settings),
    tree(compare),
    gameData(new GameData(&tree)),
    level(gameData),
    fpsText(ZIndexes::SystemText),
    frames(0),
    fpsTimer(QTime::currentTime())
{
    Fonts::InitializeFonts();
    gameData->loadLevel();
    controls.setControlledHero(&gameData->hero);
}

Engine::~Engine()
{
    delete gameData;
}

bool Engine::compare(RenderableObject *x, RenderableObject *y)
{
    if (x->getZIndex() <= y->getZIndex())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Engine::addToRenderQueue(RenderableObject *object)
{
    tree.insert(object);
}

void Engine::deleteFromRenderQueue(RenderableObject *object)
{
    tree.remove(object);
}

void Engine::countFps()
{
    char text[255];
    sprintf(text, "fps: %d", frames);
    fpsText.text.setString(text);
    frames = 0;
}

void Engine::processGameData()
{
    gameData->hero.move();
    gameData->hero.renderableObject->coords.x = round(gameData->hero.coords.x);
    gameData->hero.renderableObject->coords.y = round(gameData->hero.coords.y);
    /*if (gameData->hero.isQueueing && !gameData->hero.isQueued)
    {
        addToRenderQueue(gameData->hero.renderableObject);
        gameData->hero.isQueued = true;
    }
    else if (!gameData->hero.isQueueing && gameData->hero.isQueued)
    {
        deleteFromRenderQueue(gameData->hero.renderableObject);
        gameData->hero.isQueued = false;
    }*/
}

void Engine::processPressedKeyEvent(QKeyEvent *event)
{
    controls.processPressedHeroControls(event);
}

void Engine::processReleasedKeyEvent(QKeyEvent *event)
{
    controls.processReleasedHeroControls(event);
}

void Engine::render()
{
    ++frames;
    processGameData();

    RenderableObject *object;
    TreeNode<RenderableObject *> *iterator = NULL;
    while ((object = tree.iterate(iterator)) != NULL && object->getZIndex() < 5000)
    {
        gameData->processCoords(object);
        qDebug() << object->coords.x << object->coords.y;
        renderTarget->draw(*object->getDrawable());
    }
    // TODO: Set camera mode here.
    if (object)
    {
        while ((object = tree.iterate(iterator)) != NULL)
        {
            gameData->processCoords(object);
            renderTarget->draw(*object->getDrawable());
        }
    }
    while ((object = tree.iterate(iterator)) != NULL && object->getZIndex() < 5000)
    {
        object->resetCoordsStatus();
    }
}
