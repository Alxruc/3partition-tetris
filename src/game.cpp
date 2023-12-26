#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/game.hpp"

const float FALLSPEED = 0.05;
const int BLOCK_SIZE = 50;


void Game::init(const char* title, int x, int y, int width, int height, bool fullscreen) {
    int flags = 0;
    if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initialized";
        window = SDL_CreateWindow(title, x, y, width, height, flags);
    
        if(window) {
            std::cout << "Window created successfully" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);

        if(renderer) {
            std::cout << "Renderer created successfully" << std::endl;
        }

        isRunning = true;
    }
    else {
        isRunning = false;
    }
    this->width = width;
    this->height = height;

    
}

void Game::initPiece(SDL_Texture* tex, int type) {
    fallingPiece = Piece(width/2, 0, 0, type, tex);
}

Piece Game::getFalling() {
    return this->fallingPiece;
}

std::vector<Piece> Game::getStationary() {
    return this->stationaryPieces;
};

void Game::handleEvents(Uint32* msecondCounter) {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_LEFT: {
                    //check if there is a piece to the left of us blocking the way
                    //or the edge of the screen
                    bool blocked = false; 
                    float fY = fallingPiece.getY();
                    float fX = fallingPiece.getX();

                    for (Piece piece : stationaryPieces) {
                        float pY = piece.getY();
                        float pH = piece.getH();
                        float pX = piece.getX();
                        float pW = piece.getW();
                    
                        if ((pY <= fY && 
                            fY < pY + pH &&
                            fX - BLOCK_SIZE < pX + pW) ||
                            fX - BLOCK_SIZE < 0) {
                            // Collision detected
                            blocked = true;
                            std::cout << "blocked" << std::endl;
                            break;
                        }
                    }
                    if(!blocked) {
                        fallingPiece.setX(fallingPiece.getX() - BLOCK_SIZE);
                        //The piece should only move down once we haven't touched it for a bit to give us a chance to move
                        *msecondCounter = 0; 
                    }
                }
                break;
                case SDLK_RIGHT: {
                    //check if there is a piece to the right of us blocking the way
                    //or the edge of the screen
                    bool blocked = false; 
                    float fY = fallingPiece.getY();
                    float fX = fallingPiece.getX();
                    float fW = fallingPiece.getW();

                    for (Piece piece : stationaryPieces) {
                        float pY = piece.getY();
                        float pH = piece.getH();
                        float pX = piece.getX();
                    
                        if ((pY <= fY && 
                            fY < pY + pH &&
                            fX + fW + BLOCK_SIZE > pX) ||
                            // TODO Fix bug where it only blocks after one piece has already landed
                            fX + fW + BLOCK_SIZE > width) { 
                            // Collision detected
                            blocked = true;
                            std::cout << "blocked" << std::endl;
                            break;
                        }
                    }
                    if(!blocked) {
                        fallingPiece.setX(fallingPiece.getX() + BLOCK_SIZE);
                        //The piece should only move down once we haven't touched it for a bit to give us a chance to move
                        *msecondCounter = 0;
                    }
                }
                break;
                case SDLK_DOWN: {
                    bool blocked = false; //check if there is a piece to the right of us blocking the way
                    float fY = fallingPiece.getY();
                    float fX = fallingPiece.getX();
                    float fW = fallingPiece.getW();
                    float fH = fallingPiece.getH();
                    for (Piece piece : stationaryPieces) {
                        float pY = piece.getY();
                        float pX = piece.getX();
                        float pW = piece.getW();
                    
                        if ((fY+fH >= pY && 
                            fX >= pX &&
                            fX + fW <= pX + pW ) ||
                            fY +fH + BLOCK_SIZE > height) { //check if either colliding with block or screen edge
                            // Collision detected
                            blocked = true;
                            std::cout << "blocked" << std::endl;
                            break;
                        }
                    }
                    
                    if(!blocked) {
                        fallingPiece.setY(fallingPiece.getY() + BLOCK_SIZE);
                        *msecondCounter = 0;
                    }
                }
                break;

                //switch piece type for debugging
                case SDLK_1: {
                    SDL_Texture* I_tex = loadTexture("textures/I.png");
                    if(I_tex != nullptr) {
                        this->initPiece(I_tex, 1);
                        std::cout << "changed piece to I" << std::endl;
                    }
                }
                break;

                case SDLK_2: {
                    SDL_Texture* Sq_tex = loadTexture("textures/square.png");
                    if(Sq_tex != nullptr) {
                        initPiece(Sq_tex, 2);
                        std::cout << "changed piece to Sq" << std::endl;
                    }
                }
                break;  
                default:
                    break;
            }
            break;

        default:
            break;
    }
}

void Game::update(Uint32* msecondCounter) {
    bool collision = false;
        for (Piece piece : stationaryPieces) {
            if (fallingPiece.getY() + fallingPiece.getH() + BLOCK_SIZE > piece.getY() && 
                !(fallingPiece.getY() > piece.getY() + piece.getH() - 1) &&
                fallingPiece.getX() < piece.getX() + piece.getW() &&
                fallingPiece.getX() + fallingPiece.getW() > piece.getX()) {
                // Collision detected
                collision = true;
                break;
            }
        }

        if (!collision && fallingPiece.getY() < height - fallingPiece.getH()) {
            if(*msecondCounter >= 500) { //update pos once we have gone 500ms without adjusting piece
                fallingPiece.setY(fallingPiece.getY()+BLOCK_SIZE);
                *msecondCounter = 0;
            }
        } else {
            // Add the falling piece to the stationary pieces
            if(*msecondCounter >= 500) { //give player last chance to move into small gap for example
                std::cout << "collided" << std::endl;
                stationaryPieces.push_back(fallingPiece);
                // Spawn a new piece
                fallingPiece.setX(width / 2);   // Reset x position
                fallingPiece.setY(0);           // Reset y position
                *msecondCounter = 0;
            }
        }

}


SDL_Texture* Game::loadTexture(const char* filePath) {
    SDL_Texture* texture = nullptr;
    texture = IMG_LoadTexture(renderer, filePath);

    if(texture == nullptr) {
        std::cout << "Couldn't load texture" << std::endl;
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
    std::cout << "Game Quit" << std::endl;
}
