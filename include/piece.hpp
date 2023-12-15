#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Piece {
    public:
        Piece(double x, double y, int rotation, int type, SDL_Texture* texture);
        double getX();
        double getY();
        int getRotation();
        int getType();
        SDL_Texture* getTexture();
        SDL_Rect getCurrentFrame();


    private:
        double x;
        double y;
        int rotation;
        int type;
        SDL_Rect currentFrame;
        SDL_Texture* texture;
};