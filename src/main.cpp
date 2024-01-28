#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../include/game.hpp"
#include "../include/levelmaker.hpp"

Game *game = nullptr;
LevelMaker *levelmaker = nullptr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000; 

int main() {
    // TODO at the end: clean this up

    game = new Game();
    game->init("Tetris is hard", SDL_WINDOWPOS_CENTERED, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 10, false);

    levelmaker = new LevelMaker("demoLevel1");


    //Load textures
    SDL_Texture* I_tex = game->loadTexture("textures/I.png");
    SDL_Texture* bucket_tex = game->loadTexture("textures/border_gray.png");
    game->initPiece(I_tex, 1);

     std::vector<Bucket> buckets;

    for(int s = 0; s < levelmaker->getNumberOfBuckets(); s++) { // Example of how the level will be created
        Bucket bucket(levelmaker->getT(), s, SCREEN_HEIGHT, SCREEN_WIDTH, levelmaker->getNumberOfBuckets(), bucket_tex);
        buckets.push_back(bucket);
        game->fillGridHelper(bucket);
    }
    game->fillGridBorders(SCREEN_WIDTH, SCREEN_HEIGHT, levelmaker->getNumberOfBuckets());
    game->setBuckets(buckets);

    Uint32 msecond = 0;
    Uint32* msecondCounter = &msecond;
    
    Uint32 lastFrame = SDL_GetTicks();

    while(game->running()) {

        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 deltaTime = currentFrameTime - lastFrame;
        lastFrame = currentFrameTime;

        msecond += deltaTime;


        game->handleEvents(msecondCounter);
        game->update(msecondCounter);
        Piece fallingPiece = game->getFalling();

        game->clear();
        game->renderFalling(fallingPiece);   
        game->renderAll(SCREEN_WIDTH, levelmaker->getNumberOfBuckets());
        game->present();
    }

    game->clean();
    return 0;
}