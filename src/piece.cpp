#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/piece.hpp"

Piece::Piece(float x, float y, int rotation, int type, SDL_Texture* texture) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->texture = texture;

    blockOne.x = 0;
    blockOne.y = 0;
    blockOne.w = 50;
    blockOne.h = 50;

    blockTwo.w = 50;
    blockTwo.h = 50;

    blockThree.w = 50;
    blockThree.h = 50;

    blockFour.w = 50;
    blockFour.h = 50;

    
    
    switch(type) {
        case 1: //I
            blockTwo.x = 50;
            blockTwo.y = 0;
            blockThree.x = 100;
            blockThree.y = 0;
            blockFour.x = 150;
            blockFour.y = 0;
        break;
        case 2: // Sq
            blockTwo.x = 50;
            blockTwo.y = 0;
            blockThree.x = 0;
            blockThree.y = 50;
            blockFour.x = 50;
            blockFour.y = 50;
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
