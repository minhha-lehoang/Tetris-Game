#include "pause.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "details.hpp"

Pause::Pause() 
{
	pause_game = false;
}

Pause::Pause(int x, int y)
{
	Position.x = x;
	Position.y = y;

	pause_game = false;

	CurrentSprite = BUTTON_SPRITE_MOUSE_OUT_UNPAUSE;
}

void Pause::handleEvent(SDL_Event *e)
{
    //If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		bool inside = true;

		if( x < Position.x + button_border || x > Position.x + button_border + button_size
		|| y < Position.y + button_border || y > Position.y + button_border + button_size)
		{
			inside = false;
		}

		if( !inside )
		{
			if (!pause_game) CurrentSprite = BUTTON_SPRITE_MOUSE_OUT_UNPAUSE;
			else CurrentSprite = BUTTON_SPRITE_MOUSE_OUT_PAUSE;
		}
		else
		{
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONUP:
				{
					if (!pause_game) CurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION_UNPAUSE;
					else CurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION_PAUSE;
					break;
				}
			
				case SDL_MOUSEBUTTONDOWN: 
				{
					if (!pause_game) pause_game = true;
					else pause_game = false;

					if (!pause_game) CurrentSprite = BUTTON_SPRITE_MOUSE_DOWN_PAUSE;
					else CurrentSprite = BUTTON_SPRITE_MOUSE_DOWN_UNPAUSE;

					break;
				}
			}
		}
	}
}