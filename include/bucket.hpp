#ifndef bucket_hpp
#define bucket_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <vector>

class Bucket {
    public:
        Bucket(int T, int bucketNumber, int bottomOfScreen, int width, int totalNumberOfBuckets, SDL_Texture* texture);
        std::vector<SDL_Rect> getRects();
        SDL_Texture* getTexture();
    private:
        int T;
        int bucketNumber; // We will have s buckets and we use this to determine where to place the bucket
        std::vector<SDL_Rect> rects;
        SDL_Texture* texture;
};

#endif 