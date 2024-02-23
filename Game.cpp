#include <iostream>
#include <ctime>
#include <string>
#include "Game.hpp"
#include <cstdlib>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "highscores.hpp"

extern SDL_Renderer* gRenderer;

Pause pauseButton(pauseButtonPos.x, pauseButtonPos.y);
Pause SoundButton(holdBoxPos.x - 10, pauseButtonPos.y);
Pause MusicButton(holdBoxPos.x + 50, pauseButtonPos.y);
theme themeSwitch(themeSwitchRect.x, themeSwitchRect.y);
button restartNo(noButtonPos);
button ok(okButtonPos);

Game::Game()
{
    board = new Board;
}

Game::~Game()
{
    tetromino_graphic.free();
    tetromino_graphic_light.free();
    tetromino_graphic_dark.free();

    ghost_tetromino_graphic.free();
    ghost_tetromino_graphic_light.free();
    ghost_tetromino_graphic_dark.free();

    background.free();
    background_light.free();
    background_dark.free();

    pause_button_graphic.free();
    pause_button_graphic_light.free();
    pause_button_graphic_dark.free();

    theme_switch_graphic.free();
    theme_switch_graphic_light.free();
    theme_switch_graphic_dark.free();

    gameover.free();
    gameover_light.free();
    gameover_dark.free();

    no.free();
    no_light.free();
    no_dark.free();

    ok_graphic.free();
    ok_graphic_light.free();
    ok_graphic_dark.free();

    sound_button.free();
    sound_button_light.free();
    sound_button_dark.free();

    entername.free();
    entername_light.free();
    entername_dark.free();

    music_graphic.free();
    music_graphic_light.free();
    music_graphic_dark.free();

    MovePiece.~sound();
    ClearLine.~sound();
    Switch.~sound();
    DropPiece.~sound();
}

void Game::checkState()
{
    board->storePiece(currentPiece); //store current block
    int prevLines = board->line_cleared;
    board->deleteFullLine(); //delete full line
    if (board->line_cleared != prevLines && !isMuteSound) 
    {
        ClearLine.playSound();
        switch(board->line_cleared - prevLines)
        {
            case 1: score += 100*level();
                break;
            case 2: score += 200*level();
                break;
            case 3: score += 500*level();
                break;
            case 4: score += 800*level();
        }
    }
    if (!board->gameOver())
    {
        createNewPiece();
    }
    used_hold_block = false;
}

void Game::swap(Piece &a, Piece &b)
{
    Piece temp = currentPiece;
    currentPiece = holdPiece;
    holdPiece = temp;
}

std::string Game::clearedLines()
{
    std::string temp = "Lines: " + std::to_string(board->line_cleared);
    return temp;
}

int Game::level()
{
    int speed = board->line_cleared/10;
    if (speed > 9) speed = 9;
    return speed + 1;
}

void Game::createNewPiece()
{
    currentPiece.type = nextPiece.type;
    currentPiece.rotation = nextPiece.rotation;
    currentPiece.y = currentPiece.getBeginYPos();
    currentPiece.x = playfield_width/2 + currentPiece.getBeginXPos();

    //move new normal and null blocks into playfield
    for (int i = 0; i < 2; i++)
    {
        currentPiece.y++;
        if (!board->isMovePossible(currentPiece)) currentPiece.y--;
    }

    //move pivot block into playfield
    if (currentPiece.type > 1)
    {
        currentPiece.y++;
        if (!board->isMovePossible(currentPiece)) currentPiece.y--;
    }
    
    //randomly create new piece
    while (nextPiece.type == currentPiece.type) nextPiece.type = getRandom(0, 6);
    nextPiece.rotation = 0;
}

void Game::gameoverDraw()
{
    if (isLightMode)
    {
        gameover = gameover_light;
        no = no_light;
    } else
    {
        gameover = gameover_dark;
        no = no_dark;
    }

    gameover.render(0,0, &background_pic);
    no.render(noButtonPos.x, noButtonPos.y, &noButtonRect[restartNo.CurrentSprite]);

    texture player_rank, player_name, player_score;
    int num = numbers_of_player(highscores_path);
    for (int i = 0; i < num; i++)
    {
        player p = get_player(highscores_path, i);
        player_rank.loadText(std::to_string(i+1), text_color, gSmallFont);
        player_name.loadText(p.name, text_color, gSmallFont);
        player_score.loadText(std::to_string(p.score), text_color, gSmallFont);

        player_rank.renderCentered(370, 330 + 28 * i);
        player_name.renderCentered(460, 330 + 28 * i);
        player_score.renderCentered(570, 330 + 28 * i);
    }
}

void Game::QuitButton(SDL_Event e)
{
    restartNo.handleEvent(&e);
    if (restartNo.click)
    {
        quit = true;
        std::cout << "Action: Quit" << std::endl;
    }
}

void Game::drawEntername()
{
    if (isLightMode)
    {
        entername = entername_light;
        ok_graphic = ok_graphic_light;
    }
    else
    {
        entername = entername_dark;
        ok_graphic = ok_graphic_dark;
    }

    SDL_Rect name = { 0, 0, nameRect.w, nameRect.h };

    entername.render(nameRect.x, nameRect.y, &name);
    ok_graphic.render(okButtonPos.x, okButtonPos.y, &okButtonRect[ok.CurrentSprite]);
}

void Game::drawScene()
{
    if (isLightMode)
    {
        tetromino_graphic = tetromino_graphic_light;
        background = background_light;
        text_color = text_color_light;
        ghost_tetromino_graphic = ghost_tetromino_graphic_light;
        pause_button_graphic= pause_button_graphic_light;
        theme_switch_graphic = theme_switch_graphic_light;
        sound_button = sound_button_light;
        music_graphic = music_graphic_light;
    }
    else
    {
        tetromino_graphic = tetromino_graphic_dark;
        background = background_dark;
        text_color = text_color_dark;
        ghost_tetromino_graphic = ghost_tetromino_graphic_dark;
        pause_button_graphic = pause_button_graphic_dark;
        theme_switch_graphic = theme_switch_graphic_dark;
        sound_button = sound_button_dark;
        music_graphic = music_graphic_dark;
    }

    drawBackground();
    drawBoard();
    if (!first_time_hold) drawHoldPiece(holdPiece);
    if (!board->gameOver()) drawGhostPiece(currentPiece);
    drawCurrentPiece(currentPiece);
    drawNextPiece(nextPiece);

    if (gameOver() && isInputName) drawEntername();
    if (gameOver() && !isInputName) gameoverDraw();
}

//handling event from keyboard
void Game::event(ACTION a)
{
    switch (a)
    {
        case ACTION::down:
        {
            if (!isPause)
            {
                if (!isMuteSound) MovePiece.playSound();
                currentPiece.y++;
                if (!board->isMovePossible(currentPiece))
                {
                    currentPiece.y--;
                    checkState();
                }
                score += 10*level();
                std::cout << "Action: Soft Drop" << std::endl;
            }
            break;
        }
        
        case ACTION::left:
        {
            if (!isPause)
            {
                currentPiece.x--;
                if(!board->isMovePossible(currentPiece))
                    currentPiece.x++;
                std::cout << "Action: Move Left" << std::endl;
                if (!isMuteSound) MovePiece.playSound();
            }
            break;
        }

        case ACTION::right:
        {
            if (!isPause)
            {
                if (!isMuteSound) MovePiece.playSound();
                currentPiece.x++;
                if (!board->isMovePossible(currentPiece))
                    currentPiece.x--;
                std::cout << "Action: Move Right" << std::endl;
            }
            break;
        }

        case ACTION::drop:
        {
            if (!isPause)
            {
                if (!isMuteSound) DropPiece.playSound();
                while (board->isMovePossible(currentPiece))
                {
                    score += 20 * level();
                    currentPiece.y++;
                }
                currentPiece.y--;
                checkState();
                std::cout << "Action: Hard Drop" << std::endl;
            }
            break;
        }

        case ACTION::rotate:
        {
            if (!isPause)
            {
                if (!isMuteSound) MovePiece.playSound();
                currentPiece.rotation = (currentPiece.rotation + 1) % 4; //(0, 3)
                if (!board->isMovePossible(currentPiece))
                {
                    //if (currentPiece.x < 0) currentPiece.x++;
                    //else if (currentPiece.x >= playfield_width - 1) currentPiece.x--;
                    currentPiece.rotation = (currentPiece.rotation + 3) % 4;
                }
                std::cout << "Action: Rotate" << std::endl;
            }
            break;
        }

        case ACTION::hold:
        {
            if (!isPause)
            {
                if (!isMuteSound) MovePiece.playSound();
                if (first_time_hold)
                {
                    holdPiece = Piece(currentPiece);
                    holdPiece.rotation = 0;
                    createNewPiece();
                    first_time_hold = false;
                    used_hold_block = true;
                }
                else if (!used_hold_block)
                {
                    swap(currentPiece, holdPiece);
                    holdPiece.rotation = 0;
                    currentPiece.y = currentPiece.getBeginYPos();
                    currentPiece.x = playfield_width/2 + currentPiece.getBeginXPos();
                }

                for (int i = 0; i < 2; i++)
                {
                    currentPiece.y++;
                    if (!board->isMovePossible(currentPiece))
                        currentPiece.y--;
                }

                if (currentPiece.type > 1)
                {
                    currentPiece.y++;
                    if (!board->isMovePossible(currentPiece))
                        currentPiece.y--;
                }

                used_hold_block = true;
                std::cout << "Action: Hold" << std::endl;
            }
            break;
        }

    }
}

void Game::PauseButton(SDL_Event e)
{
    pauseButton.handleEvent(&e);
    if (isPause != pauseButton.pause_game) std::cout << "Action: Pause/Unpause" << std::endl;
    isPause = pauseButton.pause_game;
}

void Game::ThemeSwitch(SDL_Event e)
{
    themeSwitch.handleEvent(&e);
    if (isLightMode != themeSwitch.lightMode && !isMuteSound)
    {
        Switch.playSound();
        std::cout << "Action: Switch theme" << std::endl;
    }
    isLightMode = themeSwitch.lightMode;
}

void Game::MuteSound(SDL_Event e)
{
    SoundButton.handleEvent(&e);
    if (isMuteSound != SoundButton.pause_game) std::cout << "Action: Mute/Unmute sound" << std::endl;
    isMuteSound = SoundButton.pause_game;
}

void Game::MuteMusic(SDL_Event e)
{
    MusicButton.handleEvent(&e);
    if (isMuteMusic != MusicButton.pause_game) std::cout << "Action: Pause/Resume music" << std::endl;
    isMuteMusic = MusicButton.pause_game;
}

void Game::initializeScene()
{
    srand(time(0));
    score = 0;

    quit = false;
    first_time_hold = true;
    used_hold_block = false;
    isLightMode = true;
    isMuteSound = false;
    isMuteMusic = false;

    isInputName = true;

    nextPiece.type = getRandom(0, 6);
    nextPiece.rotation = 0;
    createNewPiece();
    
    nextPiece.x = nextPiecePos.x;
    nextPiece.y = nextPiecePos.y;

    tetromino_graphic_light.loadImage(minoes_path_light);
    tetromino_graphic_dark.loadImage(minoes_path_dark);
    for (int i = 0; i < 7; i++)
    {
        tetrominoes[i].x = block_size*i;
        tetrominoes[i].y = 0;
        tetrominoes[i].w = block_size;
        tetrominoes[i].h = block_size;
    }

    ghost_tetromino_graphic_light.loadImage(ghost_minoes_path_light);
    ghost_tetromino_graphic_dark.loadImage(ghost_minoes_path_dark);
    for (int i = 0; i < 7; i++)
    {
        ghost_tetrominoes[i].x = block_size*i;
        ghost_tetrominoes[i].y = 0;
        ghost_tetrominoes[i].w = block_size;
        ghost_tetrominoes[i].h = block_size;
    }

    background_light.loadImage(background_path_light);
    background_dark.loadImage(background_path_dark);
    background_pic = {0, 0, windowWidth, windowHeight};
    
    pause_button_graphic_light.loadImage(button_path_light);
    pause_button_graphic_dark.loadImage(button_path_dark);

    sound_button_light.loadImage(sound_path_light);
    sound_button_dark.loadImage(sound_path_dark);

    music_graphic_light.loadImage(music_button_light_path);
    music_graphic_dark.loadImage(music_button_dark_path);
    for (int i = 0; i < 6; i++)
    {
        pause_button[i].x = button_sprite_size * i;
        pause_button[i].y = 0;
        pause_button[i].w = button_sprite_size;
        pause_button[i].h = button_sprite_size;

        soundButtonRect[i].x = button_sprite_size * i;
        soundButtonRect[i].y = 0;
        soundButtonRect[i].w = button_sprite_size;
        soundButtonRect[i].h = button_sprite_size;

        musicButtonRect[i].x = button_sprite_size * i;
        musicButtonRect[i].y = 0;
        musicButtonRect[i].w = button_sprite_size;
        musicButtonRect[i].h = button_sprite_size;
    }

    theme_switch_graphic_light.loadImage(switch_path_light);
    theme_switch_graphic_dark.loadImage(switch_path_dark);
    theme_switch = {0, 0, themeSwitchRect.w, themeSwitchRect.h};

    gameover_light.loadImage(gameover_path_light);
    gameover_dark.loadImage(gameover_path_dark);

    no_light.loadImage(no_path_light);
    no_dark.loadImage(no_path_dark);
    for (int i = 0; i < 2; i++)
    {
        noButtonRect[i].x = noButtonPos.w*i;
        noButtonRect[i].y = 0;
        noButtonRect[i].w = noButtonPos.w;
        noButtonRect[i].h = noButtonPos.h;
    }

    entername_light.loadImage(entername_path_light);
    entername_dark.loadImage(entername_path_dark);

    ok_graphic_light.loadImage(ok_path_light);
    ok_graphic_dark.loadImage(ok_path_dark);
    for (int i = 0; i < 2; i++)
    {
        okButtonRect[i].x = okButtonPos.w * i;
        okButtonRect[i].y = 0;
        okButtonRect[i].w = okButtonPos.w;
        okButtonRect[i].h = okButtonPos.h;
    }

    soundLoad();
}

bool Game::gameOver()
{
    return board->gameOver();
}

void Game::pieceFalling()
{
    currentPiece.y++;
    if (!board->isMovePossible(currentPiece))
    {
        currentPiece.y--;
        checkState();
    }
}

void Game::soundLoad()
{
    MovePiece.loadSound(movepiece_path);
    ClearLine.loadSound(clearline_path);
    Switch.loadSound(switch_path);
    DropPiece.loadSound(droppiece_path);
}

void Game::drawBackground()
{
    background.render(0, 0, &background_pic);
    pause_button_graphic.render(pauseButtonPos.x, pauseButtonPos.y, &pause_button[pauseButton.CurrentSprite]);
    theme_switch_graphic.render(themeSwitchRect.x, themeSwitchRect.y, &theme_switch);
    sound_button.render(SoundButton.Position.x, SoundButton.Position.y, &soundButtonRect[SoundButton.CurrentSprite]);
    music_graphic.render(MusicButton.Position.x, MusicButton.Position.y, &musicButtonRect[MusicButton.CurrentSprite]);
}

void Game::drawBoard()
{
    for (int row = playfield_height - true_playfield_height; row < playfield_height; row++)
    {
        for (int col = 0; col < playfield_width; col++)
        {
            if (!board->isBlockFree(row, col))
            {
                tetromino_graphic.render(playfield.x + col*block_size,
                playfield.y + (row -(playfield_height-true_playfield_height))*block_size,
                &tetrominoes[board->getTetromino(row,col)]);
            }
        }
    }
}

void Game::drawCurrentPiece (Piece piece)
{
    for (int row = 0; row < matrix_blocks; row++)
    {
        for (int col = 0; col < matrix_blocks; col++)
        {
            if (piece.getTetromino(row, col) != 0 && (row + piece.y + 1) > (playfield_height - true_playfield_height))
            {
                tetromino_graphic.render(playfield.x + (col + piece.x)*block_size,
                playfield.y + (row + piece.y - (playfield_height - true_playfield_height))*block_size,
                &tetrominoes[piece.type]);
            }
        }
    }
    //std::cout << "current: " << piece.type << " " << piece.x << " " << piece.y << std::endl;
}

void Game::drawGhostPiece (Piece piece)
{
    ghostPiece = piece;
    while (board->isMovePossible(ghostPiece) && ghostPiece.y <= playfield.y) ghostPiece.y++;
    ghostPiece.y--;

    for (int row = 0; row < matrix_blocks; row++)
    {
        for (int col = 0; col < matrix_blocks; col++)
        {
            if (ghostPiece.getTetromino(row, col) != 0 && (row + ghostPiece.y + 1) > (playfield_height - true_playfield_height))
            {
                ghost_tetromino_graphic.render(playfield.x + (col + ghostPiece.x)*block_size,
                playfield.y + (row + ghostPiece.y - (playfield_height - true_playfield_height))*block_size,
                &ghost_tetrominoes[ghostPiece.type]);
            }
        }
    }
    //std::cout << "ghost: " << ghostPiece.type << " " << ghostPiece.x << " " << ghostPiece.y << std::endl;

}

void Game::drawHoldPiece (Piece piece)
{
    for (int row = 0; row < matrix_blocks; row++)
    {
        for (int col = 0; col < matrix_blocks; col++)
        {
            if (piece.getTetromino(row, col) != 0)
            {
                tetromino_graphic.render(holdBoxPos.x + col*block_size,
                holdBoxPos.y + row*block_size, &tetrominoes[piece.type]);
            }
        }
    }

    //std::cout << "hold: " << piece.type << " " << piece.x << " " << piece.y << std::endl;
}

void Game::drawNextPiece (Piece piece)
{
    for (int row = 0; row < matrix_blocks; row++)
    {
        for (int col = 0; col < matrix_blocks; col++)
        {
            if (piece.getTetromino(row, col) != 0)
            {
                tetromino_graphic.render(nextPiecePos.x + col*block_size,
                    nextPiecePos.y + row*block_size, &tetrominoes[piece.type]);
            }
        }
    }
    //std::cout << "next: " << piece.type << " " << piece.x << " " << piece.y << std::endl;
}

int Game::getRandom (int min, int max)
{
    return rand() % (max - min + 1) + min;
}