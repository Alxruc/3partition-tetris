#include "../include/game.hpp"
#include "../include/lock.hpp"

Lock::Lock(int T, int width, int totalNumberOfBuckets, int bottomOfScreen, SDL_Texture *texture)
{
    int levelWidth = totalNumberOfBuckets * (4 * BLOCK_SIZE) + 3 * BLOCK_SIZE; // Each bucket is 4 blocks wide + the 3 block wide lock
    this->T = T;
    this->texture = texture;

    int paddingWidth = width - levelWidth;
    int bottomPadding = (bottomOfScreen % BLOCK_SIZE);
    int leftPadding = (paddingWidth / 2) - ((paddingWidth / 2) % BLOCK_SIZE);

    for (int i = 0; i < (5 * T + 17); i++)
    {
        SDL_Rect col1;
        col1.w = BLOCK_SIZE;
        col1.h = BLOCK_SIZE;
        col1.x = leftPadding + totalNumberOfBuckets * (4 * BLOCK_SIZE);
        col1.y = bottomOfScreen - (i + 1) * BLOCK_SIZE - bottomPadding;
        rects.push_back(col1);

        if (i != (5 * T + 16))
        {
            SDL_Rect col2;
            col2.w = BLOCK_SIZE;
            col2.h = BLOCK_SIZE;
            col2.x = col1.x + BLOCK_SIZE;
            col2.y = col1.y;
            rects.push_back(col2);
        }

    }
    SDL_Rect col3;
    col3.w = BLOCK_SIZE;
    col3.h = BLOCK_SIZE;
    col3.x = leftPadding + totalNumberOfBuckets * (4 * BLOCK_SIZE) + 2 * BLOCK_SIZE;
    col3.y = bottomOfScreen - (5 * T + 17) * BLOCK_SIZE - bottomPadding;
    rects.push_back(col3);
}

std::vector<SDL_Rect> Lock::getRects()
{
    return rects;
}

SDL_Texture* Lock::getTexture()
{
    return texture;
}