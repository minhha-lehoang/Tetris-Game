#ifndef HIGHSCORES
#define HIGHSCORES

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct player
{
    string name;
    long score;
};

long lowest_highscore(string path);

void inputNew(int n, player newGamer, player gamers[], string path);

void loadScore(string path, string n, double s);

int numbers_of_player(string path);

player get_player(string path, int k);

#endif