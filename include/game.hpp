#ifndef game_hpp
#define game_hpp

#include <iostream>
#include <SDL2/SDL.h>

class Game {

public:
    void init(const char* title, int x, int y, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

};


#endif