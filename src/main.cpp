#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../include/game.hpp"

Game *game = nullptr;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600; 

int main() {

    game = new Game();
    game->init("Tetris is hard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    //Load textures
    SDL_Texture* I_tex = game->loadTexture("textures/I.png");
    game->initFirstPiece(I_tex, 1);

    
    Uint32 lastFrame = SDL_GetTicks();

    while(game->running()) {

        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 deltaTime = currentFrameTime - lastFrame;
        lastFrame = currentFrameTime;

        game->handleEvents();
        game->update(deltaTime);
        Piece fallingPiece = game->getFalling();
        std::vector<Piece> stationaryPieces = game->getStationary();

        game->clear();
        game->render(fallingPiece);   


        for (Piece piece : stationaryPieces) {
            game->render(piece);
        }

        game->present();
    }

    game->clean();
    return 0;
}