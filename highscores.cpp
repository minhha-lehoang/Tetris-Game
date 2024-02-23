#include <fstream>
#include <iostream>
#include <string>
#include "highscores.hpp"

using namespace std;

void inputNew(int n, player newGamer, player gamers[], string path)
{
    ofstream fout(path);
    if (fout.is_open())
    {
        if (n == 0)
        {
            fout << 1 << endl;
            fout << newGamer.score << endl << newGamer.name << endl;
            cout << "HIGHSCORES" << endl;
            cout << 1 << " " << newGamer.name << " " << newGamer.score << endl;
        } else
        {
            int index = n;

            for (int i = n - 1; i >= 0; i--)
            {
                if (newGamer.score > gamers[i].score)
                {
                    index--;
                } else break;
            }

            if (index < n)
            {
                for (int i = index; i < n; i++)
                {
                    player temp = newGamer;
                    newGamer = gamers[i];
                    gamers[i] = temp;
                }
            }
            cout << "HIGHSCORES" << endl;
            if (n + 1 < 5) fout << n + 1 << endl;
            else fout << 5 << endl;
            for (int i = 0; i < n; i++)
            {
                fout << gamers[i].score << endl << gamers[i].name << endl;
                cout << i+1 << " " << gamers[i].name << " " << gamers[i].score << endl;
            }
            if (n + 1 <= 5) 
            {
                fout << newGamer.score << endl << newGamer.name << endl;
                cout << n+1 << " " << newGamer.name << " " << newGamer.score << endl;
            }
        }
        fout.close();
    }
}

long lowest_highscore(string path)
{
    ifstream fin(path);
    if (fin.is_open())
    {
        int n;
        fin >> n;
        if (n == 0) return 0;
        else
        {
            long score;
            string name;
            for (int i = 0; i < n; i++)
            {
                fin >> score;
                fin.ignore();
                getline(fin, name);
            }
            return score;
        }
    }
}

void loadScore(string path, const string name, const double score)
{
    player newGamer;
    newGamer.score = score;
    newGamer.name = name;
    ifstream fin(path);
    if (fin.is_open())
    {
        int n;
        fin >> n;
        if (n > 0)
        {
            player gamers[5];
            for (int i = 0; i < n; i++)
            {
                fin >> gamers[i].score;

                fin.ignore();
                string temp;
                getline(fin, temp);
                gamers[i].name = temp;
            }
            inputNew(n, newGamer, gamers, path);
        }
        else 
        {
            player gamers[1];
            inputNew(n, newGamer, gamers, path);
        }
        fin.close();
    }
}

int numbers_of_player(string path)
{
    ifstream fin(path);
    if (fin.is_open())
    {
        int n;
        fin >> n;
        return n;
    }
}

player get_player(string path, int k)
{
    ifstream fin(path);
    if (fin.is_open())
    {
        int n;
        fin >> n;
        player temp;
        for (int i = 0; i <= k; i++)
        {
            fin >> temp.score;
            fin.ignore();
            string temp_s;
            getline(fin, temp_s);
            temp.name = temp_s;
        }
        return temp;
    }
}

