#ifndef RENDEREDOBJECT_H
#define RENDEREDOBJECT_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>

enum zIndexes {
    hero = 200,
    monsters = 100,
};

class RenderableObject
{
protected:
    // This variable defines if the coords of the object
    //were recalculated during recursive traversal.
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

    RenderableObject(unsigned int _zIndex);
    ~RenderableObject();
    unsigned int getZIndex();
};

class QueueableObject: public sf::Drawable, public sf::Transformable, public RenderableObject
{
};

class QueueableObject2: public sf::Drawable, public sf::Transformable
{
};

class RenderableSprite: public sf::Sprite, public RenderableObject
{
public:
    RenderableSprite(unsigned int _zIndex);
    sf::Texture texture;
};

class RenderableRectangle: public sf::RectangleShape, public RenderableObject
{
public:
    RenderableRectangle(unsigned int _zIndex);
};

class RenderableText: public sf::Text, public RenderableObject
{
public:
    RenderableText(unsigned int _zIndex);
};

#endif // RENDEREDOBJECT_H
