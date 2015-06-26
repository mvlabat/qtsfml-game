#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#include "fonts.h"

enum ZIndexes {
    Hero = 200,
    Monsters = 100,
    GameObjectFloatingText = 1000,
    SystemText = 9999,
};

class GameData;

class RenderableObject
{
    friend class GameData;
protected:
    // This variable defines if the coords of the object
    // has been recalculated during recursive traversal.
    bool hasCoordsPrepared;
    // Objects with lower z-index are below.
    unsigned int zIndex;
public:
    // Actual coords of object.
    sf::Vector2i coords;
    // Offset for rendering sprite.
    sf::Vector2i offset;
    // Bolean variable.
    bool isVisible;
    // Specifying parent object makes 'coords' variable relative.
    RenderableObject *parentObject;

    RenderableObject();
    RenderableObject(unsigned int _zIndex);
    ~RenderableObject();
    unsigned int getZIndex() const;
    void resetCoordsStatus();
    virtual sf::Transformable *getTransformable() = 0;
    virtual sf::Drawable *getDrawable() = 0;
};

class RenderableSprite: public RenderableObject
{
public:
    sf::Sprite sprite;
    sf::Texture texture;

    RenderableSprite(unsigned int _zIndex);
    void setTexture(const std::string&);
    sf::Transformable *getTransformable() override;
    sf::Drawable *getDrawable() override;
};

class RenderableRectangle: public RenderableObject
{
public:
    sf::RectangleShape rectangle;

    RenderableRectangle(unsigned int _zIndex);
    sf::Transformable *getTransformable() override;
    sf::Drawable *getDrawable() override;
};

class RenderableText: public RenderableObject
{
public:
    sf::Text text;

    RenderableText(unsigned int _zIndex);
    sf::Transformable *getTransformable() override;
    sf::Drawable *getDrawable() override;
};

#endif // RENDEREDOBJECT_H
