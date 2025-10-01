#ifndef BOARD_H
#define BOARD_H

#include <string>
#include <vector>
#include "defs.h"
#include "move.h"

struct Undo {
    int captured;        
    int capturedSq;      
    int epSquare_old;
    int castling_old;
    int halfmove_old;
    int fullmove_old;
    int from, to;
};

class Board {
public:
    Board();
    void loadFEN(const std::string& fen);
    void print() const;

    int at(int sq) const { return squares[sq]; }
    bool sideWhiteToMove() const { return sideToMove == WHITE; }
    int getEPSq() const { return epSquare; }
    int getCastling() const { return castlingRights; }

    void makeMove(const Move& m, Undo& st);
    void undoMove(const Move& m, const Undo& st);

    int kingSquare(Color c) const;

private:
    int squares[128]; // 0x88 board representation
    Color sideToMove;
    int castlingRights;
    int epSquare;        
    int halfmoveClock;
    int fullmoveNumber;
};

#endif
