#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/game.hpp"

const float FALLSPEED = 0.1;


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

void Game::initFirstPiece(SDL_Texture* tex, int type) {
    fallingPiece = Piece(width/2, 0, 0, type, tex);
}

Piece Game::getFalling() {
    return this->fallingPiece;
}

std::vector<Piece> Game::getStationary() {
    return this->stationaryPieces;
};

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                    case SDLK_LEFT:
                        fallingPiece.setX(fallingPiece.getX() - 50);
                        break;
                    case SDLK_RIGHT:
                        fallingPiece.setX(fallingPiece.getX() + 50);
                        break;
                    case SDLK_DOWN:
                        fallingPiece.setY(fallingPiece.getY() + 50);
                        break;
                    default:
                        break;
            }
            break;
        default:
            break;
    }
}

void Game::update(Uint32 deltaTime) {
    bool collision = false;
        for (Piece piece : stationaryPieces) {
            if (fallingPiece.getY() + fallingPiece.getH() >= piece.getY() && fallingPiece.getX() < piece.getX() + piece.getW() &&
                fallingPiece.getX() + fallingPiece.getW() > piece.getX()) {
                // Collision detected
                collision = true;
                std::cout << "collided" << std::endl;
                break;
            }
        }

        if (!collision && fallingPiece.getY() < 550) {
            fallingPiece.setY(fallingPiece.getY()+FALLSPEED*deltaTime);
        } else {
            // Add the falling piece to the stationary pieces
            stationaryPieces.push_back(fallingPiece);
            // Spawn a new piece
            fallingPiece.setX(width / 2);   // Reset x position
            fallingPiece.setY(0);           // Reset y position
        }

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
