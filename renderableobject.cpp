#include "renderableobject.h"

/**
 * RenderableObject abstract class definition.
 */

RenderableObject::RenderableObject()
{

}

RenderableObject::RenderableObject(unsigned int _zIndex) :
    hasCoordsPrepared(false),
    zIndex(_zIndex),
    coords(sf::Vector2i(0, 0)),
    isVisible(true)
{
}

RenderableObject::~RenderableObject()
{
}

unsigned int RenderableObject::getZIndex() const
{
    return zIndex;
}

void RenderableObject::resetCoordsStatus()
{
    hasCoordsPrepared = false;
}

/**
 * RenderableText class definition.
 */

RenderableText::RenderableText(unsigned int _zIndex) :
    RenderableObject::RenderableObject(_zIndex)
{
    text.setFont(Fonts::DefaultFont);
    text.setCharacterSize(10);
    text.setColor(sf::Color(255, 255, 255));
    qDebug() << "success";
}

sf::Transformable *RenderableText::getTransformable()
{
    return &text;
}

sf::Drawable *RenderableText::getDrawable()
{
    return &text;
}

/**
 * RenderableSprite class definition.
 */

RenderableSprite::RenderableSprite(unsigned int _zIndex) :
    RenderableObject::RenderableObject(_zIndex)
{
}

void RenderableSprite::setTexture(const std::string& fileName)
{
    texture.loadFromFile(fileName);
    sprite.setTexture(texture);
}

sf::Transformable *RenderableSprite::getTransformable()
{
    return &sprite;
}

sf::Drawable *RenderableSprite::getDrawable()
{
    return &sprite;
}

/**
 * RenderableRectangle class definition.
 */

sf::Transformable *RenderableRectangle::getTransformable()
{
    return &rectangle;
}

sf::Drawable *RenderableRectangle::getDrawable()
{
    return &rectangle;
}
