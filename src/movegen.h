#ifndef MOVEGEN_H
#define MOVEGEN_H

#include <vector>
#include "board.h"
#include "move.h"

void generatePseudoMoves(const Board& pos, std::vector<Move>& out);

#endif
