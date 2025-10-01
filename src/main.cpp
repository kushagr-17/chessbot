#include "board.h"
#include "movegen.h"
#include "utils.h"
#include "perft.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc >= 2 && std::string(argv[1]) == "perft") {
        if (argc < 4) {
            std::cerr << "Usage: " << argv[0] << " perft <fen> <depth>\n";
            return 1;
        }

        std::string fen = argv[2];
        int depth = std::stoi(argv[3]);

        Board board;
        board.loadFEN(fen);
        board.print();

        runPerft(board, depth);
        return 0;
    }

    Board board;
    //starting FEN notation
    std::string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    
    board.loadFEN(startFEN);
    board.print();


    // perft test
    runPerft(board, 5);

    return 0;
}
