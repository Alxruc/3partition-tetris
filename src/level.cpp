#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/piece.hpp"
#include "../include/bucket.hpp"
#include "../include/level.hpp"

#include "../include/game.hpp"


std::set<int> whichLinesNeedClearing(std::vector<std::vector<Field>> grid, Piece piece, int blocksize) {
    std::set<int> filledRows;
    std::vector<SDL_Rect> rects = piece.getRects();

    //iterate through all the parts of the piece and check if the entire y-row is filled
    for (SDL_Rect rect : rects) {
        int rectY = (piece.getY() + rect.y) / blocksize;

        bool isRowFilled = true;
        for (size_t i = 0; i < grid[rectY].size(); i++) {
            if (!grid[rectY][i].occupied) {
                isRowFilled = false;
                break;
            }
        }
        if(isRowFilled) {
            filledRows.insert(rectY);
        }
    }
    return filledRows;
}

void clearRows(std::vector<std::vector<Field>> *gridPtr, std::set<int> filledRows) {
    // Known bug: If row is cleared the top border doesnt have collision because it is simply filled with emptiness

    for (int row : filledRows) {
        std::cout << "Clearing row " << row << std::endl;
        gridPtr->erase(gridPtr->begin() + row);
        std::vector<Field> emptyRow = std::vector<Field>((*gridPtr)[0].size(), {0, 0, 0, 0, false, nullptr});

        // shifts down all the blocks from the rows above so they get rendered correctly
        for(int y = 0; y < row; y++) {
            for(size_t x = 0; x < (*gridPtr)[y].size(); x++) {
                (*gridPtr)[y][x].y += BLOCK_SIZE;
            }
        }
        gridPtr->insert(gridPtr->begin(), emptyRow);
    }
}