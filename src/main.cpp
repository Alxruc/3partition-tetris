#include <SDL2/SDL.h>
#include <iostream>
#include "../include/game.hpp"

Game *game = nullptr;

int main() {

    game = new Game();
    game->init("Tetris is hard", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

    while(game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
    return 0;
}