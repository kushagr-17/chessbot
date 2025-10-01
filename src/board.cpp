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

static inline void clearCastleRights(Board &b, int from, int to, int &rights){
    (void)b; 
}

int Board::kingSquare(Color c) const {
    int kingPiece = (c == WHITE) ? wK : bK;
    for(int sq=0;sq<128;sq++){
        if (!IS_ONBOARD(sq)) continue;
        if (squares[sq] == kingPiece) return sq;
    }
    return -1; 
}

void Board::makeMove(const Move& m, Undo& st){
    int from = m.from;
    int to = m.to;
    int piece = m.piece;

    st.captured = (m.flags & MF_CAPTURE) ? m.captured : EMPTY;
    st.capturedSq = (m.flags & MF_EPCAP) ? ((sideToMove == WHITE) ? to - 16 : to + 16) : to;
    st.epSquare_old = epSquare;
    st.castling_old = castlingRights;
    st.halfmove_old = halfmoveClock;
    st.fullmove_old = fullmoveNumber;
    st.from = from;
    st.to = to;

    epSquare = -1; 

    if(piece == wP || piece == bP || st.captured != EMPTY){
        halfmoveClock = 0;
    }
    else{
        halfmoveClock++;
    }
    if (sideToMove == BLACK) fullmoveNumber++;

    squares[from] = EMPTY;

    if(m.flags & MF_CAPTURE){
        squares[st.capturedSq] = EMPTY;
    }

    if(m.flags & MF_PROMO){
        squares[to] = m.promoted;
    }
    else{
        squares[to] = piece;
    }

    if(m.flags & MF_DBLP){
        epSquare = (from+to)/2;
    }

    if (m.flags & MF_EPCAP) {
        squares[st.capturedSq] = EMPTY;
    }

    if(m.flags & MF_CASTLE){
        // White
        if (to == SQ(6,0)) { squares[SQ(7,0)] = EMPTY; squares[SQ(5,0)] = wR; } // O-O
        if (to == SQ(2,0)) { squares[SQ(0,0)] = EMPTY; squares[SQ(3,0)] = wR; } // O-O-O

        // Black
        if (to == SQ(6,7)) { squares[SQ(7,7)] = EMPTY; squares[SQ(5,7)] = bR; } // O-O
        if (to == SQ(2,7)) { squares[SQ(0,7)] = EMPTY; squares[SQ(3,7)] = bR; } // O-O-O
    }

    if (piece == wK) castlingRights &= ~(WKCA | WQCA);
    if (piece == bK) castlingRights &= ~(BKCA | BQCA);
    if (from == SQ(0,0) || to == SQ(0,0)) castlingRights &= ~WQCA;
    if (from == SQ(7,0) || to == SQ(7,0)) castlingRights &= ~WKCA;
    if (from == SQ(0,7) || to == SQ(0,7)) castlingRights &= ~BQCA;
    if (from == SQ(7,7) || to == SQ(7,7)) castlingRights &= ~BKCA;

    sideToMove = (sideToMove == WHITE ? BLACK : WHITE);
}


void Board::undoMove(const Move& m, const Undo& st){
    int from = st.from;
    int to = st.to;
    int piece = m.piece;

    sideToMove = (sideToMove == WHITE ? BLACK : WHITE);

    epSquare = st.epSquare_old;
    castlingRights = st.castling_old;
    halfmoveClock = st.halfmove_old;
    fullmoveNumber = st.fullmove_old;

    if(m.flags & MF_CASTLE){
        // White
        if (to == SQ(6,0)) { squares[SQ(7,0)] = wR; squares[SQ(5,0)] = EMPTY; } // O-O
        if (to == SQ(2,0)) { squares[SQ(0,0)] = wR; squares[SQ(3,0)] = EMPTY; } // O-O-O

        // Black
        if (to == SQ(6,7)) { squares[SQ(7,7)] = bR; squares[SQ(5,7)] = EMPTY; } // O-O
        if (to == SQ(2,7)) { squares[SQ(0,7)] = bR; squares[SQ(3,7)] = EMPTY; } // O-O-O
    }

    squares[from] = (m.flags & MF_PROMO) ? (sideToMove == WHITE ? wP : bP) : piece;
    squares[to]   = EMPTY;

    if(st.captured != EMPTY){
        squares[st.capturedSq] = st.captured;
    }
}
