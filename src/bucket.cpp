#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/game.hpp"
#include "../include/bucket.hpp"

#include <iostream>
#include <vector>

Bucket::Bucket(int T, int bucketNumber, int bottomOfScreen, SDL_Texture* texture) {
    this->T = T;
    this->bucketNumber = bucketNumber;

    // Here we will create the rects for the bucket
    // I am breaking the bucket up into parts to easily construct it 
    // The bottom part here is the bottom 4 rows, that are all filled except for the 3rd column
    // The top part is the repeating part

    // "Bottom part"
    

    SDL_Rect bottom1;
    bottom1.w = 2 * BLOCK_SIZE;
    bottom1.h = 4 * BLOCK_SIZE;
    bottom1.x = bucketNumber * (6 * BLOCK_SIZE); // Each bucket is 6 blocks wide
    bottom1.y = bottomOfScreen - bottom1.h;
    

    SDL_Rect bottom2;
    bottom2.w = 3 * BLOCK_SIZE;
    bottom2.h = 4 * BLOCK_SIZE;
    bottom2.x = bottom1.x + 3 * BLOCK_SIZE;
    bottom2.y = bottomOfScreen - bottom2.h;

    rects.push_back(bottom1);
    rects.push_back(bottom2);

    this->texture = texture;

    // "Top part"
    // Repeating part depending on T
    for(int i = 0; i < T+3; i++) {
        SDL_Rect column4and5;
        column4and5.w = 2 * BLOCK_SIZE;
        column4and5.h = 5 * BLOCK_SIZE;
        column4and5.x = bottom1.x + 3 * BLOCK_SIZE;
        column4and5.y = bottomOfScreen - (column4and5.h +  5 * BLOCK_SIZE) - (i * 6 * BLOCK_SIZE);

        SDL_Rect column6;
        column6.w = BLOCK_SIZE;
        column6.h = 6 * BLOCK_SIZE;
        column6.x = bottom1.x + 5 * BLOCK_SIZE;
        column6.y = bottomOfScreen - (column6.h + 4 * BLOCK_SIZE) - (i * 6 * BLOCK_SIZE);  

        rects.push_back(column4and5);
        rects.push_back(column6);
    }

}


std::vector<SDL_Rect> Bucket::getRects() {
    return this->rects;
}

SDL_Texture* Bucket::getTexture() {
    return this->texture;
}