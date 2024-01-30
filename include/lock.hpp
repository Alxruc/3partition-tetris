#ifndef lock_hpp
#define lock_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

class Lock {
    public:
        Lock(int T, int width, int totalNumberOfBuckets, int bottomOfScreen, SDL_Texture* texture);
        std::vector<SDL_Rect> getRects();
        SDL_Texture* getTexture();
    private:
        int T;
        std::vector<SDL_Rect> rects;
        SDL_Texture* texture;
};


#endif 