#ifndef RENDER
#define RENDER

#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "texture.hpp"

extern SDL_Renderer* gRenderer;
extern TTF_Font* gBigFont;
extern TTF_Font* gSmallFont;

struct render
{
    ~render();

    void clearScreen ();
    void renderTexture (texture *texture, int x, int y);
    void updateScreen ();
};

#endif