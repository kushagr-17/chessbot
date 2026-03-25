#include "board.h"
#include "movegen.h"
#include "utils.h"
#include "perft.h"
#include "search.h"
#include "eval.h"
#include <iostream>
#include <vector>
#include <libgen.h>

int main(int argc, char* argv[]) {

    const char *pname = basename(argv[0]);

    // PERFT MODE 
    if(argc >= 2 && std::string(argv[1]) == "perft"){
        if(argc < 4){
            std::cerr << "Usage: .\\" << pname << " perft <fen> <depth>\n";
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

    // SIMULATION MODE 
    if(argc >= 2 && std::string(argv[1]) == "sim"){

        Board board;
        std::string startFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

        board.loadFEN(startFEN);
        board.print();

        initRandom();

        int moveCount = 0;
        const int MAX_MOVES = 40;
        const int DEPTH = 4;

        while(true){
            if(board.sideWhiteToMove()){
                Move best = searchBestMove(board, DEPTH);

                if(best.from == -1){
                    std::cout << "Game over! (White)\n";
                    break;
                }

                Undo st;
                board.makeMove(best, st);

                std::cout << "Engine (White): " << moveToStr(best) << "\n";
            } 
            else{
                Move m = searchBestMove(board, DEPTH);

                if(m.from == -1){
                    std::cout << "Game over! (Black)\n";
                    break;
                }

                Undo st;
                board.makeMove(m, st);

                std::cout << "Engine (Black): " << moveToStr(m) << "\n";
            }

            board.print();  
            std::cout << "Move: " << moveCount << "\n";
            std::cout << "Eval: " << evaluate(board) << "\n";
            moveCount++;
            if(moveCount >= MAX_MOVES){
                std::cout << "Stopping after " << MAX_MOVES << " moves.\n";
                break;
            }
        }

        return 0;
    }

    std::cout << "Usage:\n";
    std::cout << " .\\" << pname << " perft <fen> <depth>\n";
    std::cout << " .\\" << pname << " sim\n";

    return 0;
}