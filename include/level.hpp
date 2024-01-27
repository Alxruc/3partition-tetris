#ifndef level_hpp
#define level_hpp

#include "../include/piece.hpp"
#include <set>

struct Field;

std::set<int> whichLinesNeedClearing(std::vector<std::vector<Field>> grid, Piece piece, int blocksize);
void clearRows(std::vector<std::vector<Field>> *gridPtr, std::set<int> filledRows);

#endif
