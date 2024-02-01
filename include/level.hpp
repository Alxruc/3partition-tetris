#ifndef level_hpp
#define level_hpp

#include "../include/piece.hpp"
#include <set>

struct Field;

std::set<int> whichLinesNeedClearing(std::vector<std::vector<Field>> grid, Piece piece, int blocksize);
void clearRows(std::vector<std::vector<Field>> *gridPtr, std::set<int> filledRows);
void didUserWin(SDL_Renderer *renderer, int numberOfLinesToClear, int width, int height, TTF_Font* font);
void renderScore(SDL_Renderer *renderer, int numberOfLinesToClear, int width, TTF_Font* font);
void setEmptyRow(std::vector<Field> borderRow);
int getScore();

#endif
