#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H


class GameSettings
{
public:
    GameSettings();
    char getFps();
    bool getVSync();

protected:
    char fps;
    bool vSync;
};

#endif // GAMESETTINGS_H
