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
    Piece fallingPiece(SCREEN_WIDTH/2,0,0,1,I_tex);


    std::vector<Piece> stationaryPieces;
    Uint32 lastFrame = SDL_GetTicks();
    double fallSpeed = 0.1;

    while(game->running()) {

        Uint32 currentFrameTime = SDL_GetTicks();
        Uint32 deltaTime = currentFrameTime - lastFrame;
        lastFrame = currentFrameTime;

        game->handleEvents();
        game->update();
        game->clear();

        game->render(fallingPiece);

        // TODO Maybe move to game logic instead of main

        bool collision = false;
        for (Piece piece : stationaryPieces) {
            if (fallingPiece.getY() + fallingPiece.getH() >= piece.getY() && fallingPiece.getX() < piece.getX() + piece.getW() &&
                fallingPiece.getX() + fallingPiece.getW() > piece.getX()) {
                // Collision detected
                collision = true;
                std::cout << "collided";
                break;
            }
        }

        if (!collision && fallingPiece.getY() < 550) {
            fallingPiece.setY(fallingPiece.getY()+fallSpeed*deltaTime);
        } else {
            // Add the falling piece to the stationary pieces
            stationaryPieces.push_back(fallingPiece);
            // Spawn a new piece
            fallingPiece.setX(SCREEN_WIDTH / 2); // Reset x position
            fallingPiece.setY(0);                  // Reset y position
        }


        for (Piece piece : stationaryPieces) {
            game->render(piece);
        }

        game->present();
    }

    game->clean();
    return 0;
}