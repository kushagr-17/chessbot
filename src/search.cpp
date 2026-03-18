#include "search.h"
#include "eval.h"
#include "movegen.h"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

static const int INF = 30000000;
static const int MATE = 29000000;

void initRandom() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Move randomMove(Board& pos) {
    std::vector<Move> moves;
    generateLegalMoves(pos, moves);
    if (moves.empty()) return Move();
    return moves[std::rand() % moves.size()];
}

static int pieceVal(int p) {
    switch(p) {
        case wP: case bP: return 100;
        case wN: case bN: return 320;
        case wB: case bB: return 330;
        case wR: case bR: return 500;
        case wQ: case bQ: return 900;
        case wK: case bK: return 20000;
        default: return 0;
    }
}

static void orderMoves(std::vector<Move>& moves) {
    std::sort(moves.begin(), moves.end(), [](const Move& a, const Move& b) {
        int scoreA = 0, scoreB = 0;

        if (a.flags & MF_CAPTURE)
            scoreA = 10000 + pieceVal(a.captured) - pieceVal(a.piece);
        if (b.flags & MF_CAPTURE)
            scoreB = 10000 + pieceVal(b.captured) - pieceVal(b.piece);

        if (a.flags & MF_PROMO) scoreA += 9000;
        if (b.flags & MF_PROMO) scoreB += 9000;

        return scoreA > scoreB;
    });
}

// quiescence search
static void genCaptures(Board& pos, std::vector<Move>& out) {
    std::vector<Move> all;
    generateLegalMoves(pos, all);
    out.clear();
    for (auto& m : all) {
        if ((m.flags & MF_CAPTURE) || (m.flags & MF_PROMO))
            out.push_back(m);
    }
}

int quiescence(Board& pos, int alpha, int beta) {
    int stand = evaluate(pos);

    if (stand >= beta) return beta;
    if (stand > alpha) alpha = stand;

    std::vector<Move> moves;
    genCaptures(pos, moves);
    orderMoves(moves);

    Undo st;
    for (const Move& m : moves) {
        pos.makeMove(m, st);
        int score = -quiescence(pos, -beta, -alpha);
        pos.undoMove(m, st);

        if (score >= beta) return beta;
        if (score > alpha) alpha = score;
    }

    return alpha;
}

// negamax search
int negamax(Board& pos, int depth, int alpha, int beta) {
    if (depth == 0)
        return quiescence(pos, alpha, beta);

    std::vector<Move> moves;
    generateLegalMoves(pos, moves);

    if(moves.empty()){
        int kingSq = pos.kingSquare(pos.sideWhiteToMove() ? WHITE : BLACK);
        bool inCheck = isSquareAttacked(pos, kingSq, pos.sideWhiteToMove() ? BLACK : WHITE);

        if (inCheck) return -MATE + depth; 
        return 0; 
    }

    orderMoves(moves);

    Undo st;
    int best = -INF;

    for (const Move& m : moves) {
        pos.makeMove(m, st);

        int score = -negamax(pos, depth - 1, -beta, -alpha);

        pos.undoMove(m, st);

        if (score > best) best = score;
        if (score > alpha) alpha = score;
        if (alpha >= beta) break; // cutoff
    }

    return best;
}

Move searchBestMove(Board& pos, int depth) {
    std::vector<Move> moves;
    generateLegalMoves(pos, moves);

    if (moves.empty()) return Move();

    orderMoves(moves);

    Move bestMove = moves[0];
    int bestScore = -INF;

    Undo st;

    for (const Move& m : moves) {
        pos.makeMove(m, st);

        int score = -negamax(pos, depth - 1, -INF, INF);

        pos.undoMove(m, st);

        score += (std::rand() % 5);

        if (score > bestScore) {
            bestScore = score;
            bestMove = m;
        }
    }

    return bestMove;
}