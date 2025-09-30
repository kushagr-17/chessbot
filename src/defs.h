#ifndef DEFS_H
#define DEFS_H

#include <cstdint>
#include <string>

enum Color { WHITE = 0, BLACK = 1, COLOR_NB = 2 };

enum Piece {
    EMPTY = 0,
    wP, wN, wB, wR, wQ, wK,
    bP, bN, bB, bR, bQ, bK,
    PIECE_NB
};

// KCA - King side Castling
// QCA - Queen side Castling
enum Castling {
    WKCA = 1,  
    WQCA = 2,  
    BKCA = 4,  
    BQCA = 8   
};

#define IS_ONBOARD(sq) (!((sq) & 0x88))
#define FILE_OF(sq)    ((sq) & 7)
#define RANK_OF(sq)    ((sq) >> 4)
#define SQ(file,rank)  (((rank) << 4) | (file))

const int OFFBOARD = -1;

static const char PIECE_SYMBOLS[14] = ".PNBRQKpnbrqk";

static const int KN_OFF[8]  = { +33, +31, +18, +14, -14, -18, -31, -33 };
static const int RK_OFF[4]  = { +1, -1, +16, -16 };
static const int BSH_OFF[4] = { +15, +17, -15, -17 };
static const int QN_OFF[8]  = { +1, -1, +16, -16, +15, +17, -15, -17 };

static const int PAWN_PUSH[2]   = { +16, -16 };  
static const int PAWN_CAPL[2]   = { +15, -17 };  
static const int PAWN_CAPR[2]   = { +17, -15 };  
static const int PAWN_START_RANK[2] = { 1, 6 }; 
static const int PAWN_PROMO_RANK[2] = { 7, 0 };  

#endif
