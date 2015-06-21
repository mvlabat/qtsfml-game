#include "renderableobject.h"

/**
 * RenderableObject abstract class definition.
 */

RenderableObject::RenderableObject(unsigned int _zIndex) :
    hasCoordsPrepared(false),
    zIndex(_zIndex),
    isVisible(true)
{
}

RenderableObject::~RenderableObject()
{
}

unsigned int RenderableObject::getZIndex()
{
    return zIndex;
}

/**
 * RenderableText class definition.
 */

RenderableText::RenderableText(unsigned int _zIndex) :
    RenderableObject::RenderableObject(_zIndex),
    sf::Text::Text()
{
}

/**
 * RenderableSprite class definition.
 */

RenderableSprite::RenderableSprite(unsigned int _zIndex) :
    RenderableObject::RenderableObject(_zIndex),
    sf::Sprite::Sprite()
{

}
