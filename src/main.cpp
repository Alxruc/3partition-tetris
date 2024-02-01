#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../include/game.hpp"
#include "../include/levelmaker.hpp"

Game *game = nullptr;
LevelMaker *levelmaker = nullptr;

// Change this to the level you want to play
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 1000; 
const char* LEVEL_FILE = "demoLevel0";

int main() {
    // TODO at the end: clean this up
    game = new Game();
    levelmaker = new LevelMaker(LEVEL_FILE);
    std::queue<int> pieces = levelmaker->createPieceVector();
    std::queue<int> test;
    test.push(pieces.front());
    game->setPieces(test);

    int T = levelmaker->getT();
    int numOfBuckets = levelmaker->getNumberOfBuckets();

    // Here we calculate how large the blocks can be for our game
    // If we have a larger level we shrink the blocks so that everything can fit within
    // the desired dimensions
    int blocksize;
    int widthDiv = SCREEN_WIDTH / (numOfBuckets * 4 + 3);
    int heightDiv = SCREEN_HEIGHT / (5 * T + 30); //extra space at the top

    if(widthDiv < heightDiv) {
        blocksize = widthDiv;
    } else {
        blocksize = heightDiv;
    }
    game->init("Tetris is hard", SDL_WINDOWPOS_CENTERED, 0, SCREEN_WIDTH, SCREEN_HEIGHT, blocksize, false);
    game->setNumberOfLinesToClear(T);

    SDL_Texture* bucket_tex = game->loadTexture("textures/border_gray.png");
    
    game->initPiece();

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
    int i = 1;

    while(i > 0) {
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
        i--;
    }

    game->clean();
    return 0;
}