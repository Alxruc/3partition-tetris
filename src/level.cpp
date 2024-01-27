#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/piece.hpp"
#include "../include/bucket.hpp"

#include "../include/game.hpp"


std::vector<int> whichLinesNeedClearing(std::vector<std::vector<bool>> grid, Piece piece, int blocksize) {
    std::vector<int> filledRows;
    std::vector<SDL_Rect> rects = piece.getRects();
    for (SDL_Rect rect : rects) {
        int rectY = (piece.getY() + rect.y) / blocksize;

        bool isRowFilled = true;
        for (size_t i = 0; i < grid.size(); i++) {
            if (!grid[rectY][i]) {
                isRowFilled = false;
                break;
            }
        }
        if(isRowFilled) {
            filledRows.push_back(rectY);
        }
    }
    return filledRows;
}

void clearRows() {
    
}