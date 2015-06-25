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

    RenderableObject();
    RenderableObject(unsigned int _zIndex);
    ~RenderableObject();
    const unsigned int getZIndex();
    virtual sf::Transformable *getTransofmable() = 0;
    virtual sf::Drawable *getDrawable() = 0;
};

/*class QueueableObject: public sf::Drawable, public sf::Transformable, public RenderableObject
{
    QueueableObject() :
        sf::Drawable(),
        sf::Transformable(),
        RenderableObject(3)
    {

    }
};*/

class RenderableSprite: public RenderableObject
{
public:
    sf::Sprite sprite;
    sf::Texture texture;

    RenderableSprite(unsigned int _zIndex);
    sf::Transformable *getTransofmable() override;
    sf::Drawable *getDrawable() override;
};

class RenderableRectangle: public RenderableObject
{
public:
    sf::RectangleShape rectangle;

    RenderableRectangle(unsigned int _zIndex);
    sf::Transformable *getTransofmable() override;
    sf::Drawable *getDrawable() override;
};

class RenderableText: public RenderableObject
{
public:
    sf::Text text;

    RenderableText(unsigned int _zIndex);
    sf::Transformable *getTransofmable() override;
    sf::Drawable *getDrawable() override;
};

#endif // RENDEREDOBJECT_H
