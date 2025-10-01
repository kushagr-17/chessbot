#ifndef PERFT_H
#define PERFT_H

#pragma once
#include "board.h"
#include <cstdint>

class Board;

uint64_t perft(Board& pos, int depth);
uint64_t perftDivide(Board &board, int depth);
void runPerft(Board &board, int maxDepth);

#endif