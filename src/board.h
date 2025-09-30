#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "defs.h"
#include "move.h"

class Board {
public:
    Board();
    void loadFEN(const std::string& fen);
    void print() const;

    int at(int sq) const { return squares[sq]; }
    bool sideWhiteToMove() const { return sideToMove == WHITE; }
    int getEPSq() const { return epSquare; }
    int getCastling() const { return castlingRights; }

    void generatePseudoMoves(std::vector<Move>& out) const;

private:
    int squares[128]; // 0x88 board representation
    Color sideToMove;
    int castlingRights;
    int epSquare;        
    int halfmoveClock;
    int fullmoveNumber;
};

#endif
