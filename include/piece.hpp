#ifndef piece_hpp
#define piece_hpp

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <array>
#include <vector>
class Piece {
    public:
        Piece() : x(0), y(0), rotation(0), type(0), texture(nullptr) {}; //default constructor
        Piece(float x, float y, int rotation, int type, SDL_Texture* texture);
        float getX();
        float getY();
        int getH();
        int getW();
        int getRotation();
        int getType();
        void setX(float newValue);
        void setY(float newValue);
        std::array<int, 8> coordinatesOfCWRotation();
        void rotateClockWise();
        SDL_Texture* getTexture();
        std::vector<SDL_Rect> getRects();
        void setRects(std::vector<SDL_Rect> newRects);
        SDL_Rect blockOne;
        SDL_Rect blockTwo;
        SDL_Rect blockThree;
        SDL_Rect blockFour;
        std::vector<SDL_Rect> rects; //this is our tetromino made up of blocks one to four


    private:
        float x;
        float y;
        int rotation;
        int type;
        SDL_Texture* texture;
};

#endif 