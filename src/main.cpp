#include "board.h"
#include "movegen.h"
#include "utils.h"
#include <iostream>
#include <vector>

int main() {
    Board board;

    //starting FEN notation
    std::string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    
    board.loadFEN(startFEN);
    board.print();

    std::vector<Move> mv;
    generateLegalMoves(board, mv);
    std::cout << "Legal moves: " << mv.size() << "\n";
    for(size_t i=0;i<mv.size() && i<20;i++){
        std::cout << moveToStr(mv[i]) << " ";
    }
    std::cout << "\n";

    return 0;
}
