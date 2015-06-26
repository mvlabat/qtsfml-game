#include "gamesettings.h"

GameSettings::GameSettings() :
    fps(120),
    vSync(true)
{

}

char GameSettings::getFps() const
{
    return fps;
}

bool GameSettings::getVSync() const
{
    return vSync;
}

