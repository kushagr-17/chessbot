#ifndef MOVE_H
#define MOVE_H

#include "defs.h"
#include <vector>

enum MoveFlag {
    MF_NONE   = 0,
    MF_CAPTURE= 1 << 0,
    MF_PROMO  = 1 << 1,
    MF_EPCAP  = 1 << 2,
    MF_DBLP  = 1 << 3,
    MF_CASTLE = 1 << 4
};

struct Move {
    int from;
    int to;
    int piece;
    int captured;   
    int promoted;   
    int flags;      
};

#endif
