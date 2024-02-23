#include <iostream>
#include <cmath>
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>
#include "game.hpp"
#include "SDL_utils.hpp"
#include "render.hpp"
#include "pause.hpp"
#include "button.hpp"
#include "sound.hpp"
#include "highscores.hpp"
#include "music.hpp"

void game(Game &tetrisGame, input *manager, render &rRenderer, SDL_Event e)
{
    texture score;
    std::string currentScore = "Score: " + std::to_string(tetrisGame.score);
    score.loadText(currentScore, tetrisGame.text_color, gBigFont);

    texture speed;
    std::string Level = "Level: " + std::to_string(tetrisGame.level());
    speed.loadText(Level, tetrisGame.text_color, gBigFont);

    int countdown = 3; // 3... 2... 1...
    sound count_down_sound[2];
    for (int i = 0; i < 2; i++)
    {
        std::string sound_path = path + "countdown" + std::to_string(i) + ".wav";
        count_down_sound[i].loadSound(sound_path);
    }

    manager->clearQueueEvent();
    texture countdown_text;
    while (countdown > 0)
    {
        rRenderer.clearScreen();

        tetrisGame.drawScene();

        rRenderer.renderTexture(&score, 174, 560);
        rRenderer.renderTexture(&speed, 174, 600);

        countdown_text.loadText(std::to_string(countdown), tetrisGame.text_color, gBigFont);

        rRenderer.renderTexture(&countdown_text, windowWidth / 2, windowHeight / 2);

        rRenderer.updateScreen();

        count_down_sound[0].playSound();

        SDL_Delay(1000);
        countdown--;
    }
    rRenderer.clearScreen();

    music background_music;
    background_music.loadMusic(music_path);

    manager->clearQueueEvent();
   
    bool music_pause = false;

    unsigned long long time_1 = SDL_GetTicks();
    count_down_sound[1].playSound();
    if (!tetrisGame.isMuteMusic) background_music.playMusic();

    while (!tetrisGame.gameOver() && !manager->ExitGame())
    {
        long int wait_time = 1000 - (tetrisGame.level() - 1)*100;

        if (tetrisGame.isMuteMusic != music_pause)
        {
            background_music.pause_resume();
            music_pause = tetrisGame.isMuteMusic;
        }

        currentScore = "Score: " + std::to_string(tetrisGame.score);
        score.loadText(currentScore, tetrisGame.text_color, gBigFont);

        Level = "Level: " + std::to_string(tetrisGame.level());
        speed.loadText(Level, tetrisGame.text_color, gBigFont);

        unsigned long long time_2 = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0)
        {
            manager->pollAction(e);
            tetrisGame.event(manager->inputAction());
            tetrisGame.PauseButton(e);
            tetrisGame.ThemeSwitch(e);
            tetrisGame.MuteSound(e);
            tetrisGame.MuteMusic(e);
        }

        if (time_2 - time_1 >= wait_time && !tetrisGame.isPause)
        {
            tetrisGame.pieceFalling();
            time_1 = SDL_GetTicks();
        }

        rRenderer.clearScreen();
        tetrisGame.drawScene();
        rRenderer.renderTexture(&score, 174, 560);
        rRenderer.renderTexture(&speed, 174, 600);

        rRenderer.updateScreen();
    }

    std::cout << "Game Over!" << std::endl;
    background_music.stopMusic();

    if (tetrisGame.score > lowest_highscore(highscores_path) || numbers_of_player(highscores_path) < 5)
    {
        std::string newName = "";
        texture InputTextTexture;
        extern button ok;
        SDL_StartTextInput();
        bool quit = false;
        while (!quit && !ok.click)
        {
            bool renderText = false;

            while (SDL_PollEvent(&e) != 0)
            {
                if (e.type == SDL_QUIT) quit = true;
                else if (e.type == SDL_KEYDOWN)
                {
                    if( e.key.keysym.sym == SDLK_BACKSPACE && newName.length() > 0 )
                    {
                        newName.pop_back();
                        renderText = true;
                    }
                    else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                    {
                        SDL_SetClipboardText( newName.c_str() );
                    }
                    else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                    {
                        newName = SDL_GetClipboardText();
                        renderText = true;
                    }
                    else if (e.key.keysym.sym == SDLK_RETURN)
                    {
                        renderText = true;
                        ok.click = true;
                    }
                }
                else if (e.type == SDL_TEXTINPUT)
                {
                    //Not copy or pasting
                    if( !( SDL_GetModState() & KMOD_CTRL && ( e.text.text[ 0 ] == 'c' || e.text.text[ 0 ] == 'C' 
                        || e.text.text[ 0 ] == 'v' || e.text.text[ 0 ] == 'V' ) ) )
                    {
                        //Append character
                        newName += e.text.text;
                        renderText = true;
                    }
                }
                ok.handleEvent(&e);
            }
            if (renderText)
            {
                if (newName != "")
                {
                    std::cout << newName << std::endl;
                    InputTextTexture.loadText(newName, tetrisGame.text_color, gSmallFont);
                }
                else
                {
                    InputTextTexture.loadText(" ", tetrisGame.text_color, gSmallFont);
                }
            }
            rRenderer.clearScreen();
            tetrisGame.drawScene();
            rRenderer.renderTexture(&score, windowWidth / 2, windowHeight / 2 - 40);
            rRenderer.renderTexture(&InputTextTexture, windowWidth / 2, 432);

            rRenderer.updateScreen();
        }
        SDL_StopTextInput();
        tetrisGame.isInputName = false;
        InputTextTexture.free();
        loadScore(highscores_path, newName, tetrisGame.score); 
    } else tetrisGame.isInputName = false;

    score.free();
    speed.free();
    background_music.~music();
    for (int i = 0; i < 2; i++)
    {
        count_down_sound[i].~sound();
    }
    countdown_text.free();
}


int main(int argc, char **argv)
{
    input* manager = new input;
    render rRenderer;
    Game tetrisGame;

    if (initSDL())
    {
        loadGraphic();

        SDL_Event e;

        //set up game
        tetrisGame.initializeScene();

        if (SDL_PollEvent(&e) != 0)
        {
            game(tetrisGame, manager, rRenderer, e);
        }
        
        while (!manager->ExitGame() && !tetrisGame.quit)
        {
            while (SDL_PollEvent(&e) != 0 )
            {
                manager->pollAction(e);
                tetrisGame.QuitButton(e);
            }

            rRenderer.clearScreen();
            tetrisGame.drawScene();
            rRenderer.updateScreen();
        }  
    }
    tetrisGame.~Game();
    delete manager;
    close();
    
    return 0;
}