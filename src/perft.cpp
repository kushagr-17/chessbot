#include "board.h"
#include "movegen.h"
#include "utils.h"
#include <vector>
#include <cstdint>
#include <iostream>
#include <chrono>

// Reference taken from https://www.chessprogramming.org/Perft

uint64_t perft(Board& pos, int depth){
    if (depth == 0) return 1;

    std::vector<Move> moves;
    generateLegalMoves(pos, moves);

    if (depth == 1) return moves.size();

    uint64_t nodes = 0;
    Undo st;

    for (const Move& m : moves) {
        pos.makeMove(m, st);
        nodes += perft(pos, depth - 1);
        pos.undoMove(m, st);
    }

    return nodes;
}

uint64_t perftDivide(Board& pos, int depth) {
    std::vector<Move> moves;
    generateLegalMoves(pos, moves);

    uint64_t totalNodes = 0;
    Undo st;

    for (const Move& m : moves) {
        pos.makeMove(m, st);
        uint64_t cnt = perft(pos, depth - 1);
        pos.undoMove(m, st);

        std::cout << moveToStr(m) << ": " << cnt << "\n";
        totalNodes += cnt;
    }

    std::cout << "Total nodes at depth " << depth << ": " << totalNodes << "\n";
    return totalNodes;
}

void runPerft(Board& pos, int maxDepth) {
    for (int d = 1; d <= maxDepth; d++) {
        auto start = std::chrono::high_resolution_clock::now();

        uint64_t nodes = perft(pos, d);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        double nps = (elapsed.count() > 0.0) ? nodes / elapsed.count() : 0;

        std::cout << "Perft(" << d << ") = " << nodes << "  [Time: " << elapsed.count() << " sec, " << (uint64_t)nps << " NPS]\n";
    }
}