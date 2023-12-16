#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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
    this->width = width;
    this->height = height;
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

SDL_Texture* Game::loadTexture(const char* filePath) {
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(renderer, filePath);

    if(texture == nullptr) {
        std::cout << "Couldn't load texture";
    }
    return texture;
}

bool Game::running() {
    return isRunning;
}


void Game::clear() {
    SDL_RenderClear(renderer);
}


void Game::present() {
    SDL_RenderPresent(renderer);
}

void Game::render(Piece piece) {
    SDL_Rect src;
    SDL_Rect currFrame = piece.getCurrentFrame();
    src.x = 0;
    src.y = 0;
    src.w = currFrame.w;
    src.h = currFrame.h;

    SDL_Rect dst = src;
    dst.x = piece.getX();
    dst.y = piece.getY();

    SDL_RenderCopy(renderer, piece.getTexture(), &src, &dst);
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Quit";
}
