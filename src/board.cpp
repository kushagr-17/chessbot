#include "Board.h"
#include "defs.h"
#include <iostream>
#include <sstream>
#include <cctype>

Board::Board() {
    for(int i=0;i<128;i++){
        if(i & 0x88){
            squares[i] = OFFBOARD; 
        }
        else{
            squares[i] = EMPTY;
        }
    }
}

void Board::loadFEN(const std::string& fen) {
    std::istringstream ss(fen);
    std::string boardPart;
    ss >> boardPart;

    int rank = 7;
    int file = 0;

    for(char c : boardPart){
        if(c == '/'){
            rank--;
            file = 0;
        }
        else if(isdigit(c)){
            file += c - '0';
        }
        else{
            int square = SQ_INDEX(file, rank);

            switch(c){
                case 'P': squares[square] = WP; break;
                case 'N': squares[square] = WN; break;
                case 'B': squares[square] = WB; break;
                case 'R': squares[square] = WR; break;
                case 'Q': squares[square] = WQ; break;
                case 'K': squares[square] = WK; break;
                case 'p': squares[square] = BP; break;
                case 'n': squares[square] = BN; break;
                case 'b': squares[square] = BB; break;
                case 'r': squares[square] = BR; break;
                case 'q': squares[square] = BQ; break;
                case 'k': squares[square] = BK; break;
            }
            file++;
        }
    }
}

void Board::print() const {
    for(int rank=7;rank>=0;rank--){
        for(int file=0;file<8;file++){
            int square = SQ_INDEX(file, rank);
            int piece = squares[square];
            std::cout << PIECE_SYMBOLS[piece] << " ";
        }
        std::cout << "\n";
    }
}
