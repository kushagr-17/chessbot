#include "move.h"
#include "movegen.h"
#include "utils.h"
#include <vector>

static inline void addMove(std::vector<Move>& out, int from, int to, int piece, int captured, int promoted, int flags) {
    Move m; 
    m.from = from; m.to = to; m.piece = piece; m.captured = captured; m.promoted = promoted; m.flags = flags;
    out.push_back(m);
}

static void genPawnMoves(const Board& pos, std::vector<Move>& out, int sq, int piece, Color side) {
    const int push = PAWN_PUSH[side];
    const int capL = PAWN_CAPL[side];
    const int capR = PAWN_CAPR[side];
    const int promoRank = PAWN_PROMO_RANK[side];
    const int startRank = PAWN_START_RANK[side];

    int one = sq + push;
    if (IS_ONBOARD(one) && pos.at(one) == EMPTY) {
        if (RANK_OF(one) == promoRank) {
            int q = (side==WHITE)? wQ:bQ, r=(side==WHITE)? wR:bR, b=(side==WHITE)? wB:bB, n=(side==WHITE)? wN:bN;
            addMove(out, sq, one, piece, EMPTY, q, MF_PROMO);
            addMove(out, sq, one, piece, EMPTY, r, MF_PROMO);
            addMove(out, sq, one, piece, EMPTY, b, MF_PROMO);
            addMove(out, sq, one, piece, EMPTY, n, MF_PROMO);
        }
        else{
            addMove(out, sq, one, piece, EMPTY, EMPTY, MF_NONE);
            if (RANK_OF(sq) == startRank) {
                int two = one + push;
                if (IS_ONBOARD(two) && pos.at(two) == EMPTY) {
                    addMove(out, sq, two, piece, EMPTY, EMPTY, MF_DBLP);
                }
            }
        }
    }

    int l = sq + capL, r = sq + capR;
    if (IS_ONBOARD(l)) {
        int cp = pos.at(l);
        if (!isEmpty(cp) && !sameColor(piece, cp)) {
            if (RANK_OF(l) == promoRank) {
                int q = (side==WHITE)? wQ:bQ, rr=(side==WHITE)? wR:bR, b=(side==WHITE)? wB:bB, n=(side==WHITE)? wN:bN;
                addMove(out, sq, l, piece, cp, q, MF_PROMO|MF_CAPTURE);
                addMove(out, sq, l, piece, cp, rr, MF_PROMO|MF_CAPTURE);
                addMove(out, sq, l, piece, cp, b, MF_PROMO|MF_CAPTURE);
                addMove(out, sq, l, piece, cp, n, MF_PROMO|MF_CAPTURE);
            }
            else{
                addMove(out, sq, l, piece, cp, EMPTY, MF_CAPTURE);
            }
        }
    }
    if (IS_ONBOARD(r)) {
        int cp = pos.at(r);
        if (!isEmpty(cp) && !sameColor(piece, cp)) {
            if (RANK_OF(r) == promoRank) {
                int q = (side==WHITE)? wQ:bQ, rr=(side==WHITE)? wR:bR, b=(side==WHITE)? wB:bB, n=(side==WHITE)? wN:bN;
                addMove(out, sq, r, piece, cp, q, MF_PROMO|MF_CAPTURE);
                addMove(out, sq, r, piece, cp, rr, MF_PROMO|MF_CAPTURE);
                addMove(out, sq, r, piece, cp, b, MF_PROMO|MF_CAPTURE);
                addMove(out, sq, r, piece, cp, n, MF_PROMO|MF_CAPTURE);
            }
            else{
                addMove(out, sq, r, piece, cp, EMPTY, MF_CAPTURE);
            }
        }
    }

    // en passant
    int ep = pos.getEPSq();
    if (ep != -1) {
        if (ep == l) addMove(out, sq, l, piece, (side==WHITE? bP:wP), EMPTY, MF_EPCAP|MF_CAPTURE);
        if (ep == r) addMove(out, sq, r, piece, (side==WHITE? bP:wP), EMPTY, MF_EPCAP|MF_CAPTURE);
    }
}

static void genLeaper(const Board& pos, std::vector<Move>& out, int sq, int piece, const int* off, int n) {
    for(int i = 0; i < n; ++i){
        int to = sq + off[i];
        if (!IS_ONBOARD(to)) continue;
        int t = pos.at(to);
        if(isEmpty(t)){
            addMove(out, sq, to, piece, EMPTY, EMPTY, MF_NONE);
        }
        else if(!sameColor(piece, t)){
            addMove(out, sq, to, piece, t, EMPTY, MF_CAPTURE);
        }
    }
}

static void genSlider(const Board& pos, std::vector<Move>& out, int sq, int piece, const int* off, int n) {
    for(int d = 0; d < n; ++d){
        int to = sq;
        for(;;){
            to += off[d];
            if (!IS_ONBOARD(to)) break;
            int t = pos.at(to);
            if(isEmpty(t)){
                addMove(out, sq, to, piece, EMPTY, EMPTY, MF_NONE);
                continue;
            }
            if(!sameColor(piece, t)){
                addMove(out, sq, to, piece, t, EMPTY, MF_CAPTURE);
            }
            break;
        }
    }
}

static void genCastling(const Board& pos, std::vector<Move>& out, Color side) {
    const int rights = pos.getCastling();
    if(side == WHITE){
        // E1=0x04, G1=0x06, F1=0x05, C1=0x02, D1=0x03 
        // Rooks at H1=0x07, A1=0x00
        if(rights & WKCA){
            // empty F1,G1
            if (pos.at(SQ(5,0)) == EMPTY && pos.at(SQ(6,0)) == EMPTY) {
                addMove(out, SQ(4,0), SQ(6,0), wK, EMPTY, EMPTY, MF_CASTLE);
            }
        }
        if (rights & WQCA) {
            // empty D1,C1,B1
            if (pos.at(SQ(3,0)) == EMPTY && pos.at(SQ(2,0)) == EMPTY && pos.at(SQ(1,0)) == EMPTY) {
                addMove(out, SQ(4,0), SQ(2,0), wK, EMPTY, EMPTY, MF_CASTLE);
            }
        }
    }
    else{
        // E8=0x74, G8=0x76, F8=0x75; C8=0x72, D8=0x73;
        // Rooks H8=0x77, A8=0x70
        if (rights & BKCA) {
            if (pos.at(SQ(5,7)) == EMPTY && pos.at(SQ(6,7)) == EMPTY) {
                addMove(out, SQ(4,7), SQ(6,7), bK, EMPTY, EMPTY, MF_CASTLE);
            }
        }
        if (rights & BQCA) {
            if (pos.at(SQ(3,7)) == EMPTY && pos.at(SQ(2,7)) == EMPTY && pos.at(SQ(1,7)) == EMPTY) {
                addMove(out, SQ(4,7), SQ(2,7), bK, EMPTY, EMPTY, MF_CASTLE);
            }
        }
    }
}

void generatePseudoMoves(const Board& pos, std::vector<Move>& out) {
    out.clear();
    const bool white = pos.sideWhiteToMove();
    for (int sq = 0; sq < 128; ++sq) {
        if (!IS_ONBOARD(sq)) continue;
        int p = pos.at(sq);
        if (isEmpty(p)) continue;
        if (white && !isWhite(p)) continue;
        if (!white && !isBlack(p)) continue;

        switch (p) {
            case wP: genPawnMoves(pos, out, sq, p, WHITE); break;
            case bP: genPawnMoves(pos, out, sq, p, BLACK); break;

            case wN: case bN: genLeaper(pos, out, sq, p, KN_OFF, 8); break;
            case wK: case bK: genLeaper(pos, out, sq, p, QN_OFF, 8); break;

            case wB: case bB: genSlider(pos, out, sq, p, BSH_OFF, 4); break;
            case wR: case bR: genSlider(pos, out, sq, p, RK_OFF, 4);  break;
            case wQ: case bQ: genSlider(pos, out, sq, p, QN_OFF, 8);  break;
        }
    }
    genCastling(pos, out, white ? WHITE : BLACK);
}
