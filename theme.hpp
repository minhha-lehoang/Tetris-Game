#ifndef THEME
#define THEME

#include <SDL.h>
#include <stdio.h>
#include <string>
#include "texture.hpp"
#include "render.hpp"

class theme
{
private:
    SDL_Point Position;

public:
    theme();
    
    theme(int x, int y);

    bool lightMode;
    
    void handleEvent( SDL_Event* e );
};


#endif