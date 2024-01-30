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
    levelmaker = new LevelMaker("demoLevel1");
    int T = levelmaker->getT();
    int numOfBuckets = levelmaker->getNumberOfBuckets();
    int blocksize;
    int widthDiv = SCREEN_WIDTH / (numOfBuckets * 4 + 3);
    int heightDiv = SCREEN_HEIGHT / (5 * T + 25); //extra space at the top
    if(widthDiv < heightDiv) {
        blocksize = widthDiv;
    } else {
        blocksize = heightDiv;
    }


    game->init("Tetris is hard", SDL_WINDOWPOS_CENTERED, 0, SCREEN_WIDTH, SCREEN_HEIGHT, blocksize, false);

    

    //Load textures
    SDL_Texture* I_tex = game->loadTexture("textures/I.png");
    SDL_Texture* bucket_tex = game->loadTexture("textures/border_gray.png");
    
    game->initPiece(I_tex, 1);

    for(int s = 0; s < numOfBuckets; s++) { // Example of how the level will be created
        Bucket bucket(T, s, SCREEN_HEIGHT, SCREEN_WIDTH, numOfBuckets, bucket_tex);
        game->fillGridHelper(bucket);
    }
    Lock lock(T, SCREEN_WIDTH, numOfBuckets, SCREEN_HEIGHT, bucket_tex);    
    game->fillGridHelper(lock);
    game->fillGridBorders(SCREEN_WIDTH, SCREEN_HEIGHT, numOfBuckets);

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
        game->renderAll(SCREEN_WIDTH, numOfBuckets);
        game->present();
    }

    game->clean();
    return 0;
}