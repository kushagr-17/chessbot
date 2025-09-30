#ifndef UTILS_H
#define UTILS_H

#include "defs.h"
#include "move.h"
#include <string>

char pieceToChar(int piece);
int charToPiece(char c);

bool isEmpty(int p);
bool isWhite(int p);
bool isBlack(int p);
bool sameColor(int a, int b);

std::string sqToStr(int sq);
std::string moveToStr(const Move& m);

#endif
