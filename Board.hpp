#ifndef BOARD
#define BOARD

#include "Piece.hpp"
#include <vector>

//block status
enum BlockStatus: int {empty, I, J, L, O, S, Z, T};

class Board
{ 
    friend class Game;
private:
    BlockStatus boardState[playfield_height][playfield_width];
    std::vector<Piece> pieces;
    void deleteLine (int yPos);

public:
    Board();
    int getTetromino(int y, int x);
    bool isBlockFree(int y, int x);
    bool isMovePossible(Piece piece);
    void storePiece(Piece piece);
    void deleteFullLine();
    unsigned int line_cleared = 0;
    bool gameOver();
};

#endif