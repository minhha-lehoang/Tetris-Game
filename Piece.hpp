#ifndef PIECE
#define PIECE

#include "details.hpp"

struct Piece
{
    friend class Board;
    friend class Game;
public:
    //Piece(type of piece index, rotation of piece index)
    Piece (unsigned int piece_type, unsigned int piece_rotation);

    Piece (const Piece &piece);

    //row offset
    int getBeginXPos();

    //column offset
    int getBeginYPos();

    //get cell values in a 5x5 matrix
    unsigned int getTetromino (unsigned int y_index, unsigned int x_index);
    
private:
    unsigned int type, rotation;
    int x, y;
};

#endif