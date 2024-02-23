#include "render.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>

SDL_Renderer *gRenderer = nullptr;
TTF_Font *gBigFont = nullptr;
TTF_Font* gSmallFont = nullptr;

render::~render()
{
    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;
}

void render::clearScreen()
{
    SDL_SetRenderDrawColor(gRenderer, backgroundColorLight.r, backgroundColorLight.g, backgroundColorLight.b, backgroundColorLight.a);
    SDL_RenderClear(gRenderer);
}

void render::renderTexture(texture *Texture, int x, int y)
{
    Texture->renderCentered(x, y);
}

void render::updateScreen()
{
    SDL_RenderPresent(gRenderer);
}