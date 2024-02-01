#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
#include <array>

#include "../include/piece.hpp"
#include "../include/constants.hpp"

#include "../include/game.hpp"


Piece::Piece(float x, float y, int rotation, int type, SDL_Texture* texture) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->texture = texture;

    blockOne.x = 0;
    blockOne.y = 0;
    blockOne.w = BLOCK_SIZE; //BLOCK_SIZE is an external variable in game.hpp
    blockOne.h = BLOCK_SIZE;

    blockTwo.w = BLOCK_SIZE;
    blockTwo.h = BLOCK_SIZE;

    blockThree.w = BLOCK_SIZE;
    blockThree.h = BLOCK_SIZE;

    blockFour.w = BLOCK_SIZE;
    blockFour.h = BLOCK_SIZE;

    
    
    switch(type) {
        //the coordinates of the other blocks are relative to the first one at (0,0)
        // numbers in the comments in each case indicate the ordering of the blocks
        case 1: //I
            // 1 2 3 4
            blockTwo.x = BLOCK_SIZE;
            blockTwo.y = 0;
            blockThree.x = 2 * BLOCK_SIZE;
            blockThree.y = 0;
            blockFour.x = 3 * BLOCK_SIZE;
            blockFour.y = 0;
        break;
        case 2: // Square
            // 1 2
            // 3 4
            blockTwo.x = BLOCK_SIZE;
            blockTwo.y = 0;
            blockThree.x = 0;
            blockThree.y = BLOCK_SIZE;
            blockFour.x = BLOCK_SIZE;
            blockFour.y = BLOCK_SIZE;
        break;
        case 3: // Left Gun
            // 1 - -
            // 2 3 4
            blockTwo.x = 0;
            blockTwo.y = BLOCK_SIZE;
            blockThree.x = BLOCK_SIZE;
            blockThree.y = BLOCK_SIZE;
            blockFour.x = 2 * BLOCK_SIZE;
            blockFour.y = BLOCK_SIZE;
            break;
        case 4: // Right Gun
            // - - 1
            // 4 3 2
            blockTwo.x = 0;
            blockTwo.y = BLOCK_SIZE;
            blockThree.x = -BLOCK_SIZE;
            blockThree.y = BLOCK_SIZE;
            blockFour.x = -2 * BLOCK_SIZE;
            blockFour.y = BLOCK_SIZE;
            break;
        case 5: // Left Snake
            // - 1
            // 3 2
            // 4 -
            blockTwo.x = 0;
            blockTwo.y = BLOCK_SIZE;
            blockThree.x = -BLOCK_SIZE;
            blockThree.y = BLOCK_SIZE;
            blockFour.x = -BLOCK_SIZE;
            blockFour.y = 2 * BLOCK_SIZE;
            break;
        case 6: // Right Snake
            // 1 -
            // 2 3
            // - 4
            blockTwo.x = 0;
            blockTwo.y = BLOCK_SIZE;
            blockThree.x = BLOCK_SIZE;
            blockThree.y = BLOCK_SIZE;
            blockFour.x = BLOCK_SIZE;
            blockFour.y = 2 * BLOCK_SIZE;
            break;
        case 7: // T
            // - 1 -
            // 2 3 4
            blockTwo.x = -BLOCK_SIZE;
            blockTwo.y = BLOCK_SIZE;
            blockThree.x = 0;
            blockThree.y = BLOCK_SIZE;
            blockFour.x = BLOCK_SIZE;
            blockFour.y = BLOCK_SIZE;
            break;
        case 0: // end of level
            break;
        default:
            std::cout << "Invalid type in Piece Constructor" << std::endl;
            break;

    }

    rects.push_back(blockOne);
    rects.push_back(blockTwo);
    rects.push_back(blockThree);
    rects.push_back(blockFour);
}

float Piece::getX() {
    return this->x;
}

float Piece::getY() {
    return this->y;
}

int Piece::getH() {
    return this->rects[0].h;
}

int Piece::getW() {
    return this->rects[0].w;
}

int Piece::getRotation() {
    return this->rotation;
}

int Piece::getType() {
    return this->type;
}

SDL_Texture* Piece::getTexture() {
    return this->texture;
}

void Piece::setRects(std::vector<SDL_Rect> newRects) {
    this->rects = newRects;
}

std::vector<SDL_Rect> Piece::getRects() {
    return this->rects;
}

void Piece::setX(float newValue) {
    this->x = newValue;
}

void Piece::setY(float newValue) {
    this->y = newValue;
}

std::array<int, 8> Piece::coordinatesOfCWRotation() {
    // Returns the coordinates of the blocks after a clockwise rotation
    // Coordinates are returned in an array where the first two elements are the coordinates of the first block, 
    // the second two of the second block and so on
    std::array<int, 8> coordinates;

    // Get the center of rotation
    int centerX = this->rects[1].x;
    int centerY = this->rects[1].y;

    // Rotate each block around the center of rotation
    for (int i = 0; i < 8; i = i + 2) {
        // Get the coordinates of the block relative to the center of rotation
        int x = this->rects[i/2].x - centerX;
        int y = this->rects[i/2].y - centerY;

        // Rotate the block around the center of rotation
        coordinates[i] = centerX - y;
        coordinates[i+1] = centerY + x;
    }

    return coordinates;
}

void Piece::rotateClockWise() {
    // Rotate any piece clockwise by using the second block as center of rotation

    if(this->type == 2) { //we dont need to rotate the square
        return;
    }

    // Get the center of rotation
    int centerX = this->rects[1].x;
    int centerY = this->rects[1].y;

    // Rotate each block around the center of rotation
    for (int i = 0; i < 4; i++) {
        // Get the coordinates of the block relative to the center of rotation
        int x = this->rects[i].x - centerX;
        int y = this->rects[i].y - centerY;

        // Rotate the block around the center of rotation
        this->rects[i].x = centerX - y;
        this->rects[i].y = centerY + x;
    }

    this->rotation = (this->rotation + 1) % 4;
        
}
