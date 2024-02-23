#ifndef INPUT
#define INPUT

#include <SDL.h>
#include "pause.hpp"

enum ACTION{stay, down, left, right, drop, rotate, hold, pause};

class input
{
private:
    bool quit = false;
    ACTION action = ACTION::stay;

public:
    //bool isPause = false;
    void clearQueueEvent();
    ACTION inputAction();
    bool ExitGame();
    void pollAction(SDL_Event e);
    void exit(); 
};

#endif