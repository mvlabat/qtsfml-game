#include "gamedata.h"

GameData::GameData(BinarySearchTree<RenderableObject *> *p_tree) :
    tree(p_tree)
{

}

GameData::~GameData()
{

}

void GameData::loadLevel()
{
    tree->insert(hero.renderableObject);
    tree->insert(&hero.name);
}

void GameData::processCoords(RenderableObject *object)
{
    sf::Vector2f parentCoords;
    if (!object->hasCoordsPrepared)
    {
        if (object->parentObject)
        {
            if (!object->parentObject->hasCoordsPrepared)
            {
                processCoords(object->parentObject);
            }
            parentCoords = object->parentObject->getTransformable()->getPosition();
            object->getTransformable()->setPosition(parentCoords.x + object->coords.x, parentCoords.y + object->coords.y);
        }
        else
        {
            object->getTransformable()->setPosition(object->coords.x, object->coords.y);
        }
        object->hasCoordsPrepared = true;
    }
}
