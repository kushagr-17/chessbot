#ifndef DEFS_H
#define DEFS_H

#include <cstdint>
#include <string>

// Colors
enum Color{ 
    WHITE = 0, BLACK = 1, COLOR_NB = 2 
};

// Pieces
enum Piece {
    EMPTY = 0,
    WP, WN, WB, WR, WQ, WK,
    BP, BN, BB, BR, BQ, BK,
    PIECE_NB
};

enum Castling {
    WKCA = 1,  // White King-side
    WQCA = 2,  // White Queen-side
    BKCA = 4,  // Black King-side
    BQCA = 8   // Black Queen-side
};

// (0x88) board
enum Square {
    A1=0, B1, C1, D1, E1, F1, G1, H1,
    A2=16, B2, C2, D2, E2, F2, G2, H2,
    A3=32, B3, C3, D3, E3, F3, G3, H3,
    A4=48, B4, C4, D4, E4, F4, G4, H4,
    A5=64, B5, C5, D5, E5, F5, G5, H5,
    A6=80, B6, C6, D6, E6, F6, G6, H6,
    A7=96, B7, C7, D7, E7, F7, G7, H7,
    A8=112,B8, C8, D8, E8, F8, G8, H8, SQUARE_NB
};

const int OFFBOARD = -1; 

#define IS_SQ_ON_BOARD(sq) (!((sq) & 0x88))
#define SQ_INDEX(file, rank) ((rank) * 16 + (file))

const char PIECE_SYMBOLS[14] = ".PNBRQKpnbrqk";

#endif
