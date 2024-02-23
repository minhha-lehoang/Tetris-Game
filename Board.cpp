#include "Board.hpp"
#include <iostream>

Board::Board()
{
    for (int row = 0; row < playfield_height; row++)
    {
        for (int col = 0; col < playfield_width; col++)
        {
            boardState[row][col] = BlockStatus::empty;
        }
    }
}

//return type of mino of the block
int Board::getTetromino(int y, int x)
{
    return int(boardState[y][x]) - 1;
}

//return true if the block is empty
bool Board::isBlockFree(int y, int x)
{
    return (boardState[y][x] == BlockStatus::empty) ? true : false;
}

bool Board::isMovePossible(Piece piece)
{
    for (int row = piece.y; row < piece.y + matrix_blocks; row++)
    {
        for (int col = piece.x; col < piece.x + matrix_blocks; col++)
        {
            //if outside of playfield
            if (col < 0 || col > playfield_width - 1 || row > playfield_height - 1)
            {
                if (piece.getTetromino(row - piece.y, col - piece.x) != 0)
                    return false;
            }

            //if the block is already filled
            if (row >= 0)
            {
                if (piece.getTetromino(row - piece.y, col - piece.x) != 0 && !isBlockFree(row, col))
                    return false;
            }
        }
    }
    return true;
}

void Board::storePiece (Piece piece)
{
    for (int row = piece.y; row < piece.y + matrix_blocks; row++)
    {
        for (int col = piece.x; col < piece.x + matrix_blocks; col++)
        {
            if (piece.getTetromino(row - piece.y, col - piece.x) != 0)
            {
                boardState[row][col] = static_cast<BlockStatus>(1 + piece.type); 
            }
        }
    }
    pieces.push_back(piece);
}

void Board::deleteFullLine()
{
    for (int row = 0; row < playfield_height; row++)
    {
        bool isFilled = true;
        for (int col = 0; col < playfield_width; col++)
        {
            if (isBlockFree(row, col)) isFilled = false;
        }
        if (isFilled)
        {
            deleteLine(row);
            line_cleared++;
            std::cout << "Lines: " << line_cleared << std::endl;
        }
    }
}

bool Board::gameOver()
{
    bool isOver = false;

    //if the first two lines have filled block, game over
    for (int col = 0; col < playfield_width; col++)
    { 
        if (boardState[0][col] != BlockStatus::empty ||
            boardState[1][col] != BlockStatus::empty)
        {
            isOver = true;
            break;
        }
    }
    
    return isOver;
}

void Board::deleteLine(int yPos)
{
    for (int row = yPos; row > 0; row--)
    {
        for (int col = 0; col < playfield_width; col++)
        {
            boardState[row][col] = boardState[row-1][col];
        }
    }
}