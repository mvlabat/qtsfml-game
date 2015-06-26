#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "gamehero.h"
#include "binarysearchtree.h"

class GameData
{
public:
    BinarySearchTree<RenderableObject *> *tree;
    GameHero hero;
    GameHero heroClone;

    GameData(BinarySearchTree<RenderableObject *> *p_tree);
    ~GameData();
    void loadLevel();
    void processCoords(RenderableObject *object);
};

#endif // GAMEDATA_H
