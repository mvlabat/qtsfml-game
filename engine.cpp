#include "engine.h"

Engine::Engine(sf::RenderTarget *p_renderTarget, GameSettings *p_settings) :
    QObject(),
    renderTarget(p_renderTarget),
    settings(p_settings),
    tree(compare),
    gameData(new GameData()),
    level(gameData),
    fpsText(9999),
    frames(0),
    fpsTimer(QTime::currentTime())
{
    controls.setControlledHero(&gameData->hero);

    if (font.loadFromFile("font.ttf"))
    {
        fpsText.text.setFont(font);
        fpsText.text.setString("fps: ");
        fpsText.text.setCharacterSize(10);
        fpsText.text.setColor(sf::Color(255, 255, 255));
        fpsText.coords = sf::Vector2i(0, 0);
        addToRenderQueue(&fpsText);
    }
    else
    {
        qDebug() << "The font hasn't been loaded";
    }

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (std::vector<sf::VideoMode>::iterator it = modes.begin(); it != modes.end(); ++it)
    {
        qDebug() << (*it).width << ":" << (*it).height << ":" << (*it).bitsPerPixel;
    }
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
    qDebug() << gameData->hero.direction;
    gameData->hero.move();
    gameData->hero.renderableObject->coords.x = round(gameData->hero.coords.x);
    gameData->hero.renderableObject->coords.y = round(gameData->hero.coords.y);
    qDebug() << gameData->hero.coords.x << gameData->hero.coords.y;
    if (gameData->hero.isQueueing && !gameData->hero.isQueued)
    {
        addToRenderQueue(gameData->hero.renderableObject);
        gameData->hero.isQueued = true;
    }
    else if (!gameData->hero.isQueueing && gameData->hero.isQueued)
    {
        deleteFromRenderQueue(gameData->hero.renderableObject);
        gameData->hero.isQueued = false;
    }
}

void Engine::processPressedKeyEvent(QKeyEvent *event)
{
    controls.processPressedHeroControls(event);
}

void Engine::processReleasedKeyEvent(QKeyEvent *event)
{
    controls.processReleasedHeroControls(event);
}

class Test: public sf::Drawable, public sf::Transformable { };

void Engine::render()
{
    ++frames;
    processGameData();

    RenderableObject *object;
    TreeNode<RenderableObject *> *iterator = NULL;
    while ((object = tree.iterate(iterator)) != NULL)
    {
        object->getTransofmable()->setPosition(object->coords.x, object->coords.y);
        renderTarget->draw(*object->getDrawable());
    }
}
