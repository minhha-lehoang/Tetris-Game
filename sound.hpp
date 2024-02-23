#ifndef SOUND
#define SOUND

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "texture.hpp"

struct sound
{
public:
	void loadSound(std::string path);
	void playSound();
	sound();
	~sound();
private:
	Mix_Chunk* Sound;
};

#endif
