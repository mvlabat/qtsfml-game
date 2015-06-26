#include "fonts.h"

sf::Font Fonts::DefaultFont;

void Fonts::InitializeFonts()
{
    DefaultFont.loadFromFile("font.ttf");
}
