#include "SDL_utils.hpp"
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "render.hpp"
#include "Game.hpp"
#include "music.hpp"
#include "sound.hpp"

SDL_Window* gWindow = nullptr;
extern TTF_Font* gBigFont;
extern TTF_Font* gSmallFont;
extern SDL_Renderer* gRenderer;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void logSDL_ttf_Error(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << TTF_GetError() << std::endl;
    if (fatal) {
        TTF_Quit();
        exit(1);
    }
}

void logSDL_image_Error(std::ostream& os, const std::string &msg, bool fatal)
{
    os << msg << " Error: " << IMG_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

//close gWindow, free memory 
void close()
{
    TTF_CloseFont(gBigFont);
    TTF_CloseFont(gSmallFont);
    gBigFont = nullptr;
    gSmallFont = nullptr;

    SDL_DestroyRenderer(gRenderer);
    gRenderer = nullptr;

    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;

    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

//return true if initialize game successfully
bool initSDL()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        logSDLError(std::cout, "SDL_Init", true);
        success = false;
    }
    else
    {
        gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
        if (gWindow == nullptr) //error
        {    
            logSDLError(std::cout, "CreateWindow", true);
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == nullptr)
            {
                logSDLError(std::cout, "CreateRenderer", true);
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); //white
                SDL_RenderClear(gRenderer);
                if (IMG_Init(IMG_INIT_PNG) == 0 || IMG_Init(IMG_INIT_JPG) == 0)
                {
                    logSDL_image_Error(std::cout, "Could not initialize SDL_image", true);
                    success = false;
                }
                if (TTF_Init() == -1)
                {
                    logSDL_ttf_Error(std::cout, "Could not initialize SDL_ttf", true);
                    success = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
                Mix_Volume(-1, MIX_MAX_VOLUME / 2);
                SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
                SDL_RenderSetLogicalSize(gRenderer, windowWidth, windowHeight);
            }
        }
    }
    return success;
}

//return true if load all graphics (image, gFont) successfully 
void loadGraphic()
{
    gBigFont = TTF_OpenFont(font_path_neu.c_str(), 28);
    gSmallFont = TTF_OpenFont(font_path_neu.c_str(), 14);
    if (gBigFont == nullptr || gSmallFont == nullptr)
        logSDL_ttf_Error(std::cout, "Could not load font", true);
}