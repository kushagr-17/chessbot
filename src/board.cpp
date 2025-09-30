#include "board.h"
#include "defs.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <vector>
#include <string>
#include "utils.h"
#include "move.h"

Board::Board() {
    for(int i=0;i<128;i++){
        squares[i] = (i & 0x88) ? OFFBOARD : EMPTY;
    }
    sideToMove = WHITE;
    castlingRights = 0;
    epSquare = -1;
    halfmoveClock = 0;
    fullmoveNumber = 1;
}

void Board::loadFEN(const std::string& fen) {
    for(int i=0;i<128;i++){
        squares[i] = (i & 0x88) ? OFFBOARD : EMPTY;
    }
    sideToMove = WHITE; castlingRights = 0; epSquare = -1; halfmoveClock = 0; fullmoveNumber = 1;

    std::istringstream ss(fen);
    std::string boardPart, stm, castling, ep;
    ss >> boardPart >> stm >> castling >> ep >> halfmoveClock >> fullmoveNumber;

    int sq = SQ(0,7);
    for(char c : boardPart){
        if(c == '/'){
            sq -= 24;
            continue;
        }  
        if(std::isdigit((unsigned char)c)){
            sq += c - '0';
            continue;
        }
        squares[sq++] = charToPiece(c);
    }

    sideToMove = (stm == "w") ? WHITE : BLACK;

    if (castling.find('K') != std::string::npos) castlingRights |= WKCA;
    if (castling.find('Q') != std::string::npos) castlingRights |= WQCA;
    if (castling.find('k') != std::string::npos) castlingRights |= BKCA;
    if (castling.find('q') != std::string::npos) castlingRights |= BQCA;

    if(ep != "-" && ep.size() == 2){
        int f = ep[0] - 'a';
        int r = ep[1] - '1';
        epSquare = SQ(f, r);
    }
    else{
        epSquare = -1;
    }
}

void Board::print() const {
    for(int r=7;r>=0;r--){
        std::cout << (r+1) << " ";
        for(int f=0;f<8;f++){
            int sq = SQ(f, r);
            int p = squares[sq];
            std::cout << (p == EMPTY ? ". " : std::string(1, pieceToChar(p)) + " ");
        }
        std::cout << "\n";
    }
    std::cout << "  a b c d e f g h\n";
}
