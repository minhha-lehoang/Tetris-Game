#ifndef MUSIC
#define MUSIC

#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

struct music
{
public:
    music();
    ~music();
    void loadMusic(std::string path);
    void playMusic();
    void pause_resume();
    void stopMusic();
private:
    Mix_Music* Music;
};

#endif 