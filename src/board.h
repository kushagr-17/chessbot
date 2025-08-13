#ifndef BOARD_H
#define BOARD_H

#include <string>

class Board {
public:
    Board();
    void loadFEN(const std::string& fen);
    void print() const;

private:
    int squares[128]; // 0x88 board representation
};

#endif
