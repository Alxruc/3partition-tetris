#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/piece.hpp"

Piece::Piece(float x, float y, int rotation, int type, SDL_Texture* texture) {
    this->x = x;
    this->y = y;
    this->type = type;
    this->texture = texture;

    currentFrame.x = 0;
    currentFrame.y = 0;
    
    switch(type) {
        case 1: //I
        currentFrame.w = 200;
        currentFrame.h = 50;
    }


}

float Piece::getX() {
    return this->x;
}

float Piece::getY() {
    return this->y;
}

int Piece::getH() {
    return this->currentFrame.h;
}

int Piece::getW() {
    return this->currentFrame.w;
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

SDL_Rect Piece::getCurrentFrame() {
    return this->currentFrame;
}

void Piece::setX(float newValue) {
    this->x = newValue;
}

void Piece::setY(float newValue) {
    this->y = newValue;
}
