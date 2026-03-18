#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <vector>
#include "board.h"
#include "move.h"

void generatePseudoMoves(const Board& pos, std::vector<Move>& out);
void generateLegalMoves(Board& pos, std::vector<Move>& out);

bool isSquareAttacked(const Board& pos, int sq, Color bySide);

#endif
