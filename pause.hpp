#ifndef PAUSE
#define PAUSE

#include <SDL.h>
#include <stdio.h>
#include <string>
#include "texture.hpp"
#include "render.hpp"

enum PauseButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT_UNPAUSE = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION_UNPAUSE = 1,
	BUTTON_SPRITE_MOUSE_DOWN_PAUSE = 2,
	BUTTON_SPRITE_MOUSE_OUT_PAUSE = 3,
	BUTTON_SPRITE_MOUSE_OVER_MOTION_PAUSE = 4,
	BUTTON_SPRITE_MOUSE_DOWN_UNPAUSE = 6
};

class Pause
{
	friend class Game;
	friend class input;
    public:
		Pause();

		Pause(int x, int y);

		bool pause_game;

		//Handles mouse event
		void handleEvent( SDL_Event* e );
    private:
        //Top left position
		SDL_Point Position;

		//Currently used global sprite
		PauseButtonSprite CurrentSprite;

};

#endif