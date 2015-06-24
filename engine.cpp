#include "engine.h"

Engine::Engine(sf::RenderTarget *p_renderTarget, GameSettings *p_settings) :
    QObject(),
    renderTarget(p_renderTarget),
    settings(p_settings),
    tree(compare),
    level(&gameData),
    fpsText(9999),
    frames(0),
    fpsTimer(QTime::currentTime())
{
    controls.setControlledHero(&gameData.hero);

    if (font.loadFromFile("font.ttf"))
    {
        fpsText.setFont(font);
        fpsText.setString("fps: ");
        fpsText.setCharacterSize(10);
        fpsText.setColor(sf::Color(255, 255, 255));
        fpsText.coords = sf::Vector2i(0, 0);
        addToRenderQueue((QueueableObject*)&fpsText);
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
}

bool Engine::compare(QueueableObject *x, QueueableObject *y)
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

void Engine::addToRenderQueue(QueueableObject *object)
{
    tree.insert(object);
}

void Engine::deleteFromRenderQueue(QueueableObject *object)
{
    tree.remove(object);
}

void Engine::countFps()
{
    char text[255];
    sprintf(text, "fps: %d", frames);
    fpsText.setString(text);
    frames = 0;
}

void Engine::processGameData()
{
    if (gameData.hero.isQueueing && !gameData.hero.isQueued)
    {
        addToRenderQueue((QueueableObject *)gameData.hero.queueableObject);
        gameData.hero.isQueued = true;
    }
    else if (!gameData.hero.isQueueing && gameData.hero.isQueued)
    {
        deleteFromRenderQueue((QueueableObject *)gameData.hero.queueableObject);
        gameData.hero.isQueued = false;
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

    QueueableObject *object;
    /*TreeNode<QueueableObject *> *iterator = NULL;
    while ((object = tree.iterate(iterator)) != NULL)
    {
        object->setPosition(round(object->coords.x), round(object->coords.y));
        renderTarget->draw(*(sf::Drawable *)object);
    }*/
    QueueableObject *a = (QueueableObject *)&fpsText;
    QueueableObject *b = (QueueableObject *)gameData.hero.queueableObject;
    qDebug() << a->getZIndex() << " " << fpsText.getZIndex();
    qDebug() << b->getZIndex() << " " << gameData.hero.queueableObject->getZIndex();
    renderTarget->draw(*a);
    renderTarget->draw(*(sf::Drawable *)b);
}
