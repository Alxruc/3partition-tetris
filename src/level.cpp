#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/bucket.hpp"
#include "../include/piece.hpp"
#include "../include/game.hpp"

#include <vector>
#include <iostream>

std::vector<std::vector<bool>> grid;

void setupGrid(int width, int height) {
    int numOfCols = int(width/BLOCK_SIZE);
    int numOfRows = int(height/BLOCK_SIZE);
    std::vector<bool> row(numOfCols, false);
    for(int i = 0; i < numOfRows; i++) {
        grid.push_back(row);
    }
}

void updateGrid(Bucket bucket) {
    std::vector<SDL_Rect> rects = bucket.getRects();
    for(SDL_Rect rect : rects) {
        // since bucket rects have varying sizes we first have to get width and height
        int width = rect.w;
        int height = rect.h;
        int x = rect.x;
        int y = rect.y;
        int col = int(x/BLOCK_SIZE);
        int row = int(y/BLOCK_SIZE);
        int numOfCols = int(width/BLOCK_SIZE);
        int numOfRows = int(height/BLOCK_SIZE);

        for(int i = 0; i < numOfRows; i++) {
            for(int j = 0; j < numOfCols; j++) {
                grid[row + i][col + j] = true;
            }
        }
    }
}

void updateGrid(Piece piece) {
    std::vector<SDL_Rect> rects = piece.getRects();
    for(int i = 0; i < 4; i++) {
        SDL_Rect rect = rects[i];
        int x = piece.getX() + rect.x;
        int y = piece.getY() + rect.y;
        int col = int(x/BLOCK_SIZE);
        int row = int(y/BLOCK_SIZE);
        grid[row][col] = true;
    }
}


std::vector<int> getToBeClearedRows(Piece fallingPiece, std::vector<Piece> stationaryPieces, std::vector<Bucket> buckets, int width) {
    // this function only gets called when fallingPiece touched something and will become stationary
    std::vector<int> clearedRows;
    
    return clearedRows;
}


