#include "Board.h"
#include "defs.h"
#include <iostream>

int main() {
    Board board;

    //starting FEN notation
    std::string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
    
    board.loadFEN(startFEN);
    board.print();

    return 0;
}
