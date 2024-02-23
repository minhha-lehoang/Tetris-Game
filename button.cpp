#include "button.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "details.hpp"

button::button(int x, int y, int w, int h)
{
    Box.x = x;
    Box.y = y;
    Box.w = w;
    Box.h = h;

    CurrentSprite = BUTTON_SPRITE_OUT;
    click = false;
}

button::button(SDL_Rect r)
{
    Box = r;
}

void button::handleEvent(SDL_Event *e)
{
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
    {
        //Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		bool inside = true;

        if (x < Box.x || x > Box.x + Box.w || y < Box.y || y > Box.y + Box.h)
        {
            inside = false;
        }

        if (!inside)
        {
            CurrentSprite = BUTTON_SPRITE_OUT;
        }
        else
        {
            switch(e->type)
            {
                case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONUP:
                {
                    CurrentSprite = BUTTON_SPRITE_OVER;
                    click = false;
                    break;
                }

                case SDL_MOUSEBUTTONDOWN: 
                {
                    CurrentSprite = BUTTON_SPRITE_OVER;
                    click = true;
                    break;
                }
            }
        }
    }
}