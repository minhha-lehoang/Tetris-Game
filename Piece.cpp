#include "Piece.hpp"

Piece::Piece(unsigned int piece_type, unsigned int piece_rotation)
{
    type = piece_type;
    rotation = piece_rotation;
}

Piece::Piece (const Piece &piece)
{
    type = piece.type;
    rotation = piece.rotation;
    x = piece.x;
    y = piece.y;
}

unsigned int Piece::getTetromino (unsigned int y_index, unsigned int x_index)
{
    return tetrominoes_type[type][rotation][y_index][x_index];
}

int Piece::getBeginXPos()
{
    return beginPosition[type][rotation][0];
}

int Piece::getBeginYPos()
{
    return beginPosition[type][rotation][1];
}

