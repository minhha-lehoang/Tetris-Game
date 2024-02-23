#ifndef DETAILS
#define DETAILS

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

/* PIECE */

const char tetrominoes_name[] = {'I', 'J', 'L', 'O', 'S', 'Z', 'T'};

//shape of tetrominoes in 5x5 matrixes
const int tetrominoes_type[7][4][5][5] = 
{
    //I
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 1},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {1, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },

    //J
    {
        {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },

    //L
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },

    //O
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        }
    },

    //S
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },

    //Z
    {
        {
            {0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 1, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0}
        }
    },

    //T
    {
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0},
            {0, 1, 2, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 2, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0}
        }
    }
};
const int beginPosition[7][4][2] = 
{
    //I
    {
        {-2, -3},
        {0, -3},
        {-2, -2},
        {0, -3}
    },

    //J
    {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -3}
    },

    //L
    {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -3}
    },

    //O
    {
        {-2, -3},
        {-2, -3},
        {-2, -2},
        {-2, -3}
    },

    //S
    {
        {-2, -3},
        {-2, -3},
        {-2, -2},
        {-2, -3}
    },

    //Z
    {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -3}
    },

    //T
    {
        {-2, -3},
        {-2, -3},
        {-2, -3},
        {-2, -3}
    }
};

const std::string path = "../resources/";

/* BOARD */

const SDL_Point playfield = {340, 120};
const int block_size = 28;              // in pixels
const int playfield_width = 10;         // in blocks
const int true_playfield_height = 20;   // in blocks
const int playfield_height = 22;       // The playfield + 2 rows directly above it for spawning the Tetrominos
const int board_height = 32;             // distance from botton where the playfield begins; in pixels
const int matrix_blocks = 5;            //5 x 5 matrix for each piece

/* BUTTON */

const int button_sprite_size = 68; // in pixels
const int button_size = 36;
const int button_border = (button_sprite_size - button_size)/2;
static std::string button_path_light = path + "pause_light.png";
static std::string button_path_dark = path + "pause_dark.png";

/* SWITCH */
const SDL_Rect themeSwitchRect = {724, 46, 80, 36};
static std::string switch_path_light = path + "theme_switch_light.png";
static std::string switch_path_dark = path + "theme_switch_dark.png";

/* INPUT */
const SDL_Point pauseButtonPos = {808, 30};

/* TEXTURE */
const int windowWidth = 960;
const int windowHeight = 720;
const char title[] = "TETRIS GAME";

/* RENDER */
const SDL_Color backgroundColorLight = {216, 236, 233, 255};

/* GAME */
const SDL_Point nextPiecePos = {720, 120};

const SDL_Point holdBoxPos = {100, 120};

const SDL_Color text_color_light = {8, 29, 42, 255}; //dark blue
const SDL_Color text_color_dark = { 255, 240, 238, 255 }; //light blue

static std::string minoes_path_light = path + "minoes-neumorphism_light.png";
static std::string background_path_light = path + "Neumorphism_light.png";
static std::string ghost_minoes_path_light = path + "minoes-neumorphism_ghost_light.png";

static std::string minoes_path_dark = path + "minoes-neumorphism_dark.png";
static std::string background_path_dark = path + "Neumorphism_dark.png";
static std::string ghost_minoes_path_dark = path + "minoes-neumorphism_ghost_dark.png";

static std::string font_path_neu = path + "Quicksand-Bold.ttf";

/* GAMEOVER */

static std::string gameover_path_light = path + "gameover_light.png";
static std::string gameover_path_dark = path + "gameover_dark.png";

static std::string no_path_light = path + "no_button_light.png";
static std::string no_path_dark = path + "no_button_dark.png";
const SDL_Rect noButtonPos = {windowWidth/2 - 40, 466, 80, 40};

static std::string entername_path_light = path + "entername_light.png";
static std::string entername_path_dark = path + "entername_dark.png";
const SDL_Rect nameRect = { 313, 205, 334, 310 };

static std::string ok_path_light = path + "ok_name_light.png";
static std::string ok_path_dark = path + "ok_name_dark.png";
const SDL_Rect okButtonPos = { 455, 460, 70, 40 };

static std::string highscores_path = path + "highscores.txt";

/* SOUND */

static std::string sound_path_light = path + "sound_light.png";
static std::string sound_path_dark = path + "sound_dark.png";
static std::string movepiece_path = path + "movepiece.wav";
static std::string clearline_path = path + "clearline.wav";
static std::string switch_path = path + "switch.wav";
static std::string droppiece_path = path + "droppiece.wav";

/* MUSIC */
static std::string music_path = path + "background_music.mp3";
static std::string music_button_light_path = path + "music_light.png";
static std::string music_button_dark_path = path + "music_dark.png";

#endif