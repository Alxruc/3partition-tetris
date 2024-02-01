#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>

#include "../include/piece.hpp"
#include "../include/bucket.hpp"
#include "../include/level.hpp"

#include "../include/game.hpp"

int score = 0;
std::vector<Field> emptyRow; // saving an empty row after the creation of the border for faster row clearing

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
    for (int row : filledRows) {
        std::cout << "Clearing row " << row << std::endl;
        gridPtr->erase(gridPtr->begin() + row);
        
        
        if(emptyRow.empty()) { // should be initialized but just to check
            std::cout<<"test"<<std::endl;
            emptyRow = std::vector<Field>((*gridPtr)[0].size(), {0, 0, 0, 0, false, nullptr});
        }
        // shifts down all the blocks from the rows above so they get rendered correctly
        for(int y = 0; y < row; y++) {
            for(size_t x = 0; x < (*gridPtr)[y].size(); x++) {
                (*gridPtr)[y][x].y += BLOCK_SIZE;
            }
        }
        gridPtr->insert(gridPtr->begin(), emptyRow);
        score++;
    }
}

void didUserWin(SDL_Renderer *renderer, int numberOfLinesToClear, int width, int height, TTF_Font* font) {
    TTF_SetFontSize(font, 40);
    if(score >= numberOfLinesToClear) {
        SDL_Color color = {255, 255, 255};
        std::stringstream ss;
        ss << "You found a valid 3-PARTITION!";
        SDL_Surface *surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
        SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect scoreRect = {width / 2 - surface->w / 2, height / 2 - surface->h / 2, surface->w, surface->h};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(scoreTexture);
    }
    else {
        SDL_Color color = {255, 255, 255};
        std::stringstream ss;
        ss << "You lost!";
        SDL_Surface *surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
        SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect scoreRect = {width / 2 - surface->w / 2, height / 2 - surface->h / 2, surface->w, surface->h};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(scoreTexture);
    }
}

void renderScore(SDL_Renderer *renderer, int numberOfLinesToClear, int width, TTF_Font* font) {
    SDL_Color color = {255, 255, 255};
    std::stringstream ss;
    ss << "Rows cleared: " << score;
    SDL_Surface *surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect scoreRect = {width - 100, 0, surface->w, surface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(scoreTexture);

    ss.clear();
    ss.str("");
    ss << "Amount to clear: " << numberOfLinesToClear - score;
    surface = TTF_RenderText_Solid(font, ss.str().c_str(), color);
    SDL_Texture* maxTexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect maxRect = {width - 120, 20, surface->w, surface->h};
    SDL_RenderCopy(renderer, maxTexture, NULL, &maxRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(maxTexture);
}

void setEmptyRow(std::vector<Field> borderRow) {
    emptyRow = borderRow;
}

int getScore() {
    return score;
}