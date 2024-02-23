#include "theme.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "details.hpp"

theme::theme() 
{
    lightMode = true;
}

theme::theme(int x, int y)
{
    Position.x = x;
	Position.y = y;

    lightMode = true;
}

void theme::handleEvent(SDL_Event *e)
{
    if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        int x, y;
        SDL_GetMouseState( &x, &y );
        bool inside = true;

        if (x < Position.x || x > Position.x + themeSwitchRect.w
        || y < Position.y || y > Position.y + themeSwitchRect.y)
        {
            inside = false;
        }
        else
        {
            if (e->type == SDL_MOUSEBUTTONDOWN)
            {
                if (!lightMode) lightMode = true;
                else lightMode = false;
            }
        }
    }
}