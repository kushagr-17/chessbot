#include "eval.h"
#include "defs.h"

// piece values
static const int pieceValue[PIECE_NB] = {
    0,
    100,   // wP
    320,   // wN
    330,   // wB
    500,   // wR
    900,   // wQ
    20000, // wK
    -100,  // bP
    -320,  // bN
    -330,  // bB
    -500,  // bR
    -900,  // bQ
    -20000 // bK
};

static const int pawnTable[8][8] = {
    { 0, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 5, 5, 5, 5, 5, 5, 5 },
    { 1, 1, 2, 3, 3, 2, 1, 1 },
    { 0, 0, 0, 2, 2, 0, 0, 0 },
    { 0, 0, 0, -2, -2, 0, 0, 0 },
    { 1, -1, -2, 0, 0, -2, -1, 1 },
    { 1, 2, 2, -2, -2, 2, 2, 1 },
    { 0, 0, 0, 0, 0, 0, 0, 0 }
};

static const int knightTable[8][8] = {
    {-5,-4,-3,-3,-3,-3,-4,-5},
    {-4,-2, 0, 0, 0, 0,-2,-4},
    {-3, 0, 1, 1, 1, 1, 0,-3},
    {-3, 0, 1, 2, 2, 1, 0,-3},
    {-3, 0, 1, 2, 2, 1, 0,-3},
    {-3, 0, 1, 1, 1, 1, 0,-3},
    {-4,-2, 0, 0, 0, 0,-2,-4},
    {-5,-4,-3,-3,-3,-3,-4,-5}
};

int evaluate(const Board& pos) {
    int score = 0;

    int whiteBishops = 0;
    int blackBishops = 0;

    for(int sq = 0; sq < 128; sq++){
        if(!IS_ONBOARD(sq)) continue;

        int p = pos.at(sq);
        if(p == EMPTY) continue;

        score += pieceValue[p];

        int file = FILE_OF(sq);
        int rank = RANK_OF(sq);

        switch(p){
            case wP:
                score += pawnTable[rank][file];
                break;
            case bP:
                score -= pawnTable[7 - rank][file];
                break;

            case wN:
                score += knightTable[rank][file];
                break;
            case bN:
                score -= knightTable[7 - rank][file];
                break;

            case wB: whiteBishops++; break;
            case bB: blackBishops++; break;

            default:
                break;
        }
    }

    if (whiteBishops >= 2) score += 50;
    if (blackBishops >= 2) score -= 50;

    return score; // return w.r.t white (no racism intended)
}