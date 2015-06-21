#include "gamesettings.h"

GameSettings::GameSettings() :
    fps(60),
    vSync(true)
{

}

char GameSettings::getFps()
{
    return fps;
}

bool GameSettings::getVSync()
{
    return vSync;
}

