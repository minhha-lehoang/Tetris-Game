#ifndef TEXTURE
#define TEXTURE

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "details.hpp"

class texture
{
private:
    SDL_Texture *mTexture;
    int width;
    int height;

public:
    texture();
    ~texture();
    void free();

    bool loadImage(std::string path);
    bool loadText(std::string text, SDL_Color color, TTF_Font* font);
    void render (int x, int y, SDL_Rect *clip); 
    void renderCentered (int x, int y);

    int getWidth();
    int getHeight();
};

#endif