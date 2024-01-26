#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#include "../include/piece.hpp"
#include "../include/bucket.hpp"
#include "../include/constants.hpp"

extern int BLOCK_SIZE;

class Game {

public:
    void init(const char* title, int x, int y, int width, int height, int blocksize, bool fullscreen);
    void initPiece(SDL_Texture* tex, int type);
    Piece getFalling();
    std::vector<Piece> getStationary();
    void setBuckets(std::vector<Bucket> buckets);
    void handleEvents(Uint32* msecondCounter);
    void update(Uint32* msecondCounter);
    SDL_Texture* loadTexture(const char* filePath);
    void changeBlockSize(int newBlockSize);
    void fillGridHelper(Bucket bucket);
    bool running();
    void clear();
    void present();
    void clearRows(std::vector<int> filledRows);
    void render(std::vector<Bucket> buckets);
    void render(Piece piece);
    void clean();
    std::vector<std::vector<bool>> grid;


private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
    Piece fallingPiece;
    std::vector<Piece> stationaryPieces;
    std::vector<Bucket> buckets;
    void handleLeft(Uint32* msecondCounter);
    void handleRight(Uint32* msecondCounter);
    void handleDown(Uint32* msecondCounter);
    void handleRotate(Uint32* msecondCounter);
};


#endif