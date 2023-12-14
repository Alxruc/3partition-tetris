#include <SDL2/SDL.h>
#include <iostream>

#include "../include/game.hpp"

void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized";
        window = SDL_CreateWindow(title, x, y, width, height, flags);
    
        if(window) {
            std::cout << "Window created successfully";
        }

        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer) {
            std::cout << "Renderer created successfully";
        }

        isRunning = true;
    }
    else {
        isRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void Game::update() {

}

bool Game::running() {
    return isRunning;
}

void Game::render() {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Quit";
}
