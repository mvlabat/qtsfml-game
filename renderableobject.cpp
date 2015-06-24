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
    //sf::Text::Text(),
    RenderableObject::RenderableObject(_zIndex)
{
}

/**
 * RenderableSprite class definition.
 */

RenderableSprite::RenderableSprite(unsigned int _zIndex) :
    //sf::Sprite::Sprite(),
    RenderableObject::RenderableObject(_zIndex)
{

}
