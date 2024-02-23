#include "music.hpp"
#include "texture.hpp"

music::music()
{
    Music = nullptr;
}

music::~music()
{
    Mix_FreeMusic(Music);
    Music = nullptr;
}

void music::loadMusic(std::string path)
{
    Music = Mix_LoadMUS(path.c_str());
    
    if( Music == nullptr )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
	}
}

void music::playMusic()
{
    if( Mix_PlayingMusic() == 0 ) Mix_PlayMusic(Music, -1);
}

void music::pause_resume()
{
    //If the music is paused
    if( Mix_PausedMusic() == 1 )
    {
        //Resume the music
        Mix_ResumeMusic();
    }
    //If the music is playing
    else
    {
        //Pause the music
        Mix_PauseMusic();
    }
}

void music::stopMusic()
{
    Mix_HaltMusic();
}