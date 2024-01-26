#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/game.hpp"
#include "../include/bucket.hpp"

#include <iostream>
#include <vector>

Bucket::Bucket(int T, int bucketNumber, int bottomOfScreen, SDL_Texture* texture) {
    this->T = T;
    this->bucketNumber = bucketNumber;
    this->texture = texture;

    // Here we will create the rects for the bucket
    // I am breaking the bucket up into parts to easily construct it 
    // From paper:
    // " The first column is empty except that the lowest two rows are full"
    // " The second column is completely empty"
    // " The third column is full in each row h === {1,2,3} (mod 5) and [empty otherwise]"
    // " The fourth column is completely full"

    
    // The left side of the bottom part

    SDL_Rect col1;
    col1.w = BLOCK_SIZE;
    col1.h = 2 * BLOCK_SIZE;
    col1.x = bucketNumber * (4 * BLOCK_SIZE); // Each bucket is 4 blocks wide
    col1.y = bottomOfScreen - col1.h;
    rects.push_back(col1);
    
    // The repeating part
    for(int i = 0; i < (T+4); i++) {
        SDL_Rect col3;
        col3.w = BLOCK_SIZE;
        col3.h = 3 * BLOCK_SIZE;
        col3.x = bucketNumber * (4 * BLOCK_SIZE) + 2 * BLOCK_SIZE;
        col3.y = bottomOfScreen - (5 * i * BLOCK_SIZE) - (3 * BLOCK_SIZE);
        rects.push_back(col3);
    }

    // TODO: still causes a small rendering bug, but has correct collision
    SDL_Rect col4;
    col4.w = BLOCK_SIZE;
    col4.h = (5*T + 18) * BLOCK_SIZE;
    col4.x = bucketNumber * (4 * BLOCK_SIZE) + 3 * BLOCK_SIZE;
    col4.y = bottomOfScreen - col4.h;
    rects.push_back(col4);
   

}


std::vector<SDL_Rect> Bucket::getRects() {
    return this->rects;
}

SDL_Texture* Bucket::getTexture() {
    return this->texture;
}