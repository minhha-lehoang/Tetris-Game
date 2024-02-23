#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "texture.hpp"

// SDL_Window *window;
extern SDL_Renderer* gRenderer;

texture::texture()
{
    mTexture = nullptr;
    width = 0;
    height = 0;
}

texture::~texture()
{
    free();
}

void texture::free()
{
    if(mTexture != nullptr)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = nullptr;
        width = 0;
        height = 0;
    }
}

bool texture::loadImage (std::string path)
{
    bool success = true;
    //Get rid of preexisting texture
    free();

    //temporary surface
    SDL_Surface *temp = IMG_Load(path.c_str());
    if (temp == NULL)
    {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        bool success = true;
    }
    else
    {
        //Color key image
		//SDL_SetColorKey(temp, SDL_TRUE, SDL_MapRGB( temp->format, 255, 255, 255 ) );

        mTexture = SDL_CreateTextureFromSurface(gRenderer, temp);
        if (mTexture == nullptr)
        {
            std::cout << "Unable to create texture from "  << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        else 
        { 
            //Get image dimensions
            width = temp->w;
            height = temp->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(temp);
    }
    //std::cout << "Load image: " << success << std::endl;
    return success;

}

bool texture::loadText(std::string text, SDL_Color color, TTF_Font* font)
{
    bool success = true;
    free();
    SDL_Surface *textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, windowWidth);
    if (textSurface == nullptr)
    {        
        std::cout << "SDL_ttf error: " << TTF_GetError() << std::endl; 
        success = false;
    }   
     else
    {
        mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        if (mTexture == nullptr)
            {
                std::cout << "SDL error: " << SDL_GetError() << std::endl;
                success = false;
            }
        else
        {
            width = textSurface->w;
            height = textSurface->h;
        }
    }
    SDL_FreeSurface(textSurface);
    //std::cout << "Load text: " << success << std::endl;
    return success;
}

void texture::render (int x, int y, SDL_Rect *clip)
{
    //Set rendering space and render to screen
    SDL_Rect r = {x, y, width, height};

	//Set clip rendering dimensions
    if (clip != nullptr)
    {
        r.w = clip->w;
        r.h = clip->h;
    }
    
	//Render to screen
    SDL_RenderCopy(gRenderer, mTexture, clip, &r);
}

void texture::renderCentered (int x, int y)
{
    SDL_Rect rect = {x - (width/2), y - (height/2), width, height};

    SDL_RenderCopy(gRenderer, mTexture, nullptr, &rect);
}

int texture::getWidth()
{
    return width;
}

int texture::getHeight()
{
    return height;
}