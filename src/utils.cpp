#include <cctype>
#include "utils.h"
#include "move.h"

char pieceToChar(int piece){
    if(piece >= 0 && piece < 13){
        return PIECE_SYMBOLS[piece];
    }
    return '.';
}

int charToPiece(char c){
    switch (c) {
        case 'P': return wP; case 'N': return wN; case 'B': return wB;
        case 'R': return wR; case 'Q': return wQ; case 'K': return wK;
        case 'p': return bP; case 'n': return bN; case 'b': return bB;
        case 'r': return bR; case 'q': return bQ; case 'k': return bK;
        default: return EMPTY;
    }
}

bool isEmpty(int p){
    return p == EMPTY;
}

bool isWhite(int p){
    return p >= wP && p <= wK;

}
bool isBlack(int p){
    return p >= bP && p <= bK;
}

bool sameColor(int a, int b){
    if(isEmpty(a) || isEmpty(b)){
        return false;
    }
    return (isWhite(a) && isWhite(b)) || (isBlack(a) && isBlack(b));
}

std::string sqToStr(int sq){
    char f = 'a' + FILE_OF(sq);
    char r = '1' + RANK_OF(sq);
    return std::string() + f + r;
}
std::string moveToStr(const Move& m){
    std::string s = sqToStr(m.from) + sqToStr(m.to);
    if(m.promoted != EMPTY){
        char pc = pieceToChar(m.promoted);
        s += static_cast<char>( ::tolower(static_cast<unsigned char>(pc)) );
    }
    return s;
}