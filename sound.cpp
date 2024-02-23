#include "sound.hpp"

void sound::loadSound(std::string path)
{
	Sound = Mix_LoadWAV(path.c_str());
	if (Sound == nullptr)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void sound::playSound()
{
	Mix_PlayChannel(-1, Sound, 0);
}

sound::sound()
{
	Sound = nullptr;
}

sound::~sound()
{
	Mix_FreeChunk(Sound);
	Sound = nullptr;
}
