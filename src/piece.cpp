#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/piece.hpp"
#include "../include/constants.hpp"


Piece::Piece(float x, float y, int rotation, int type, SDL_Texture* texture) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->texture = texture;

    blockOne.x = 0;
    blockOne.y = 0;
    blockOne.w = constants::BLOCK_SIZE;
    blockOne.h = constants::BLOCK_SIZE;

    blockTwo.w = constants::BLOCK_SIZE;
    blockTwo.h = constants::BLOCK_SIZE;

    blockThree.w = constants::BLOCK_SIZE;
    blockThree.h = constants::BLOCK_SIZE;

    blockFour.w = constants::BLOCK_SIZE;
    blockFour.h = constants::BLOCK_SIZE;

    
    
    switch(type) {
        //the coordinates of the other blocks are relative to the first one at (0,0)
        // numbers in the comments in each case indicate the ordering of the blocks
        case 1: //I
            // 1 2 3 4
            blockTwo.x = constants::BLOCK_SIZE;
            blockTwo.y = 0;
            blockThree.x = 2 * constants::BLOCK_SIZE;
            blockThree.y = 0;
            blockFour.x = 3 * constants::BLOCK_SIZE;
            blockFour.y = 0;
        break;
        case 2: // Square
            // 1 2
            // 3 4
            blockTwo.x = constants::BLOCK_SIZE;
            blockTwo.y = 0;
            blockThree.x = 0;
            blockThree.y = constants::BLOCK_SIZE;
            blockFour.x = constants::BLOCK_SIZE;
            blockFour.y = constants::BLOCK_SIZE;
        break;
        case 3: // Left Gun
            // 1 - -
            // 2 3 4
            blockTwo.x = 0;
            blockTwo.y = constants::BLOCK_SIZE;
            blockThree.x = constants::BLOCK_SIZE;
            blockThree.y = constants::BLOCK_SIZE;
            blockFour.x = 2 * constants::BLOCK_SIZE;
            blockFour.y = constants::BLOCK_SIZE;
            break;
        case 4: // Right Gun
            // - - 1
            // 4 3 2
            blockTwo.x = 0;
            blockTwo.y = constants::BLOCK_SIZE;
            blockThree.x = -constants::BLOCK_SIZE;
            blockThree.y = constants::BLOCK_SIZE;
            blockFour.x = -2 * constants::BLOCK_SIZE;
            blockFour.y = constants::BLOCK_SIZE;
            break;
        case 5: // Left Snake
            // - 1
            // 3 2
            // 4 -
            blockTwo.x = 0;
            blockTwo.y = constants::BLOCK_SIZE;
            blockThree.x = -constants::BLOCK_SIZE;
            blockThree.y = constants::BLOCK_SIZE;
            blockFour.x = -constants::BLOCK_SIZE;
            blockFour.y = 2 * constants::BLOCK_SIZE;
            break;
        case 6: // Right Snake
            // 1 -
            // 2 3
            // - 4
            blockTwo.x = 0;
            blockTwo.y = constants::BLOCK_SIZE;
            blockThree.x = constants::BLOCK_SIZE;
            blockThree.y = constants::BLOCK_SIZE;
            blockFour.x = constants::BLOCK_SIZE;
            blockFour.y = 2 * constants::BLOCK_SIZE;
            break;
        case 7: // T
            // - 1 -
            // 2 3 4
            blockTwo.x = -constants::BLOCK_SIZE;
            blockTwo.y = constants::BLOCK_SIZE;
            blockThree.x = 0;
            blockThree.y = constants::BLOCK_SIZE;
            blockFour.x = constants::BLOCK_SIZE;
            blockFour.y = constants::BLOCK_SIZE;
            break;
        default:
            std::cout << "Invalid type in Piece Constructor" << std::endl;
            break;

    }

    rects[0] = blockOne;
    rects[1] = blockTwo;
    rects[2] = blockThree;
    rects[3] = blockFour;

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

SDL_Rect* Piece::getRects() {
    return this->rects;
}

void Piece::setX(float newValue) {
    this->x = newValue;
}

void Piece::setY(float newValue) {
    this->y = newValue;
}
