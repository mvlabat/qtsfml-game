#include "engine.h"

Engine::Engine(sf::RenderTarget *p_renderTarget, GameSettings *p_settings) :
    QObject(),
    renderTarget(p_renderTarget),
    settings(p_settings),
    tree(compare),
    gameData(new GameData()),
    level(new Level(gameData)),
    font(),
    fpsText(new RenderableText(9999)),
    frames(0),
    fpsTimer(new QTimer(this))
{
    fpsTimer->setInterval(1000);
    connect(fpsTimer, SIGNAL(timeout()), this, SLOT(countFps()));
    fpsTimer->start();

    if (font.loadFromFile("font.ttf"))
    {
        fpsText->setFont(font);
        fpsText->setString("fps: ");
        fpsText->setCharacterSize(10);
        fpsText->setColor(sf::Color(255, 255, 255));
        fpsText->coords = sf::Vector2i(20, 20);
        addToRenderQueue((QueueableObject*)fpsText);
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
    delete level;
    delete fpsText;
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
    fpsText->setString(text);
    frames = 0;
}

void Engine::parseGameData()
{
    if (gameData->hero.isQueueing && !gameData->hero.isQueued)
    {
        addToRenderQueue((QueueableObject *)gameData->hero.queueableObject);
        gameData->hero.isQueued = true;
    }
    else if (!gameData->hero.isQueueing && gameData->hero.isQueued)
    {
        deleteFromRenderQueue((QueueableObject *)gameData->hero.queueableObject);
        gameData->hero.isQueued = false;
    }
}

void Engine::render()
{
    ++frames;
    parseGameData();

    QueueableObject *object;
    TreeNode<QueueableObject *> *iterator = NULL;
    while ((object = tree.iterate(iterator)) != NULL)
    {
        renderTarget->draw(*object);
    }
}
