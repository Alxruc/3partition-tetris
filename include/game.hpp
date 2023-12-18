#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "../include/piece.hpp"

class Game {

public:
    void init(const char* title, int x, int y, int width, int height, bool fullscreen);
    void initFirstPiece(SDL_Texture* tex, int type);

    Piece getFalling();
    std::vector<Piece> getStationary();

    void handleEvents();
    void update(Uint32 deltaTime);
    SDL_Texture* loadTexture(const char* filePath);
    bool running();
    void clear();
    void present();
    void render(Piece piece);
    void clean();
    


    

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
    Piece fallingPiece;
    std::vector<Piece> stationaryPieces;

};


#endif