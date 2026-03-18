#ifndef SEARCH_H
#define SEARCH_H

#include "board.h"
#include "move.h"

void initRandom();

Move randomMove(Board& pos);

Move searchBestMove(Board& pos, int depth);

int negamax(Board& pos, int depth, int alpha, int beta);
int quiescence(Board& pos, int alpha, int beta);

#endif