#include <SDL2/SDL.h>
#include <iostream>
#include "../include/game.hpp"

Game *game = nullptr;

int main() {

    game = new Game();
    game->init("Tetris is hard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    //Load textures
    SDL_Texture* I_tex = game->loadTexture("textures/I.png");
    Piece I_Piece(100,100,0,0,I_tex);


    while(game->running()) {
        game->handleEvents();
        game->update();
        game->clear();
        game->render(I_Piece);
        game->present();
    }

    game->clean();
    return 0;
}