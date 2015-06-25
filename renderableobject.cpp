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
    isVisible(true)
{
}

RenderableObject::~RenderableObject()
{
}

const unsigned int RenderableObject::getZIndex()
{
    return zIndex;
}

/**
 * RenderableText class definition.
 */

RenderableText::RenderableText(unsigned int _zIndex) :
    RenderableObject::RenderableObject(_zIndex)
{
}

sf::Transformable *RenderableText::getTransofmable()
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

sf::Transformable *RenderableSprite::getTransofmable()
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

sf::Transformable *RenderableRectangle::getTransofmable()
{
    return &rectangle;
}

sf::Drawable *RenderableRectangle::getDrawable()
{
    return &rectangle;
}
