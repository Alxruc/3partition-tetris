#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <vector>
#include <set>
#include <SDL2/SDL.h>

#include "../include/piece.hpp"
#include "../include/bucket.hpp"
#include "../include/constants.hpp"

extern int BLOCK_SIZE;

struct Field {
    int x;
    int y;
    int w;
    int h;
    bool occupied;
    SDL_Texture* texture;
};

class Game {

public:
    std::string fieldToString(const Field& field);
    void init(const char* title, int x, int y, int width, int height, int blocksize, bool fullscreen);
    void initPiece(SDL_Texture* tex, int type);
    Piece getFalling();
    void setBuckets(std::vector<Bucket> buckets);
    void handleEvents(Uint32* msecondCounter);
    void update(Uint32* msecondCounter);
    SDL_Texture* loadTexture(const char* filePath);
    void changeBlockSize(int newBlockSize);
    void fillGridHelper(Bucket bucket);
    bool running();
    void clear();
    void present();
    void renderFalling(Piece piece);
    void renderAll();
    void clean();
    
    


private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    int width;
    int height;
    Piece fallingPiece;
    std::vector<Bucket> buckets;
    std::vector<std::vector<Field>> grid;
    void handleLeft(Uint32* msecondCounter);
    void handleRight(Uint32* msecondCounter);
    void handleDown(Uint32* msecondCounter);
    void handleRotate(Uint32* msecondCounter);
};


#endif