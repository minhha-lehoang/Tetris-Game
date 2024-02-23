#ifndef BUTTON
#define BUTTON

#include <SDL.h>
#include <SDL_image.h>

enum ButtonSprite
{
    BUTTON_SPRITE_OUT = 0,
    BUTTON_SPRITE_OVER = 1
};

class button
{
    friend class Game;
public:
    button(int x, int y, int w, int h);
    button(SDL_Rect r);

    bool click;

    //Handles mouse event
    void handleEvent(SDL_Event* e);
private:
    SDL_Rect Box;

    ButtonSprite CurrentSprite;
};

#endif