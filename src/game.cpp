#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>

#include "../include/game.hpp"
#include "../include/constants.hpp"
#include "../include/bucket.hpp"

SDL_Texture *I_tex;
SDL_Texture *Sq_tex;
SDL_Texture *LG_tex;
SDL_Texture *RG_tex;
SDL_Texture *LS_tex;
SDL_Texture *RS_tex;
SDL_Texture *T_tex;

int BLOCK_SIZE = constants::DEFAULT_BLOCK_SIZE;

void Game::init(const char *title, int x, int y, int width, int height, int blocksize, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Initialized" << std::endl;
        window = SDL_CreateWindow(title, x, y, width, height, flags);

        if (window)
        {
            std::cout << "Window created successfully" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);

        if (renderer)
        {
            std::cout << "Renderer created successfully" << std::endl;
        }

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    this->width = width;
    this->height = height;
    I_tex = loadTexture("textures/I_lightBlue.png");
    Sq_tex = loadTexture("textures/square_yellow.png");
    LG_tex = loadTexture("textures/leftGun_darkBlue.png");
    RG_tex = loadTexture("textures/rightGun_orange.png");
    LS_tex = loadTexture("textures/leftSnake_red.png");
    RS_tex = loadTexture("textures/rightSnake_green.png");
    T_tex = loadTexture("textures/T_magenta.png");
    if (!I_tex || !Sq_tex || !LG_tex || !RG_tex || !LS_tex || !RS_tex || !T_tex)
    {
        std::cout << "Error loading textures!" << std::endl;
        isRunning = false;
    }
    BLOCK_SIZE = blocksize;

    std::cout << "width: " << width / BLOCK_SIZE << " height: " << height / BLOCK_SIZE << std::endl;

    grid = std::vector<std::vector<bool>>(width / BLOCK_SIZE, std::vector<bool>(height / BLOCK_SIZE, false));
}

void Game::initPiece(SDL_Texture *tex, int type)
{
    int center = (width / 2 / BLOCK_SIZE) * BLOCK_SIZE; // make it so it isnt a small offset with different BLOCK_SIZES
    fallingPiece = Piece(center, 0, 0, type, tex);
}

Piece Game::getFalling()
{
    return this->fallingPiece;
}

std::vector<Piece> Game::getStationary()
{
    return this->stationaryPieces;
};

void Game::setBuckets(std::vector<Bucket> buckets)
{
    this->buckets = buckets;
}

void Game::handleLeft(Uint32 *msecondCounter)
{
    // check if there is a piece to the left of us blocking the way
    // or the edge of the screen
    bool blocked = false;

    std::vector<SDL_Rect> fallingRects = fallingPiece.getRects();
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect fallingRect = fallingRects[i];
        // get the absolute coords of the rects
        float fY = fallingPiece.getY() + fallingRect.y;
        float fX = fallingPiece.getX() + fallingRect.x;
        // get the grid coordinates
        int gridX = fX / BLOCK_SIZE;
        int gridY = fY / BLOCK_SIZE;

        if(gridX - 1 < 0 ) {
            blocked = true;
            break;
        }
        if (grid[gridX - 1][gridY])
        {
            blocked = true;
            break;
        }
        
    }
    if (!blocked)
    {
        fallingPiece.setX(fallingPiece.getX() - BLOCK_SIZE);
        // The piece should only move down once we haven't touched it for a bit to give us a chance to move
        *msecondCounter = 0;
    }
}

void Game::handleRight(Uint32 *msecondCounter)
{
    // check if there is a piece to the right of us blocking the way
    // or the edge of the screen
    bool blocked = false;
    std::vector<SDL_Rect> fallingRects = fallingPiece.getRects();

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect fallingRect = fallingRects[i];
        // get the absolute coords of the rects
        float fY = fallingPiece.getY() + fallingRect.y;
        float fX = fallingPiece.getX() + fallingRect.x;

        // get the grid coordinates
        int gridX = fX / BLOCK_SIZE;
        int gridY = fY / BLOCK_SIZE;

        if(gridX + 1 >= width / BLOCK_SIZE) {
            blocked = true;
            break;
        }
        if (grid[gridX + 1][gridY])
        {
            blocked = true;
            break;
        }
    }

    if (!blocked)
    {
        fallingPiece.setX(fallingPiece.getX() + BLOCK_SIZE);
        // The piece should only move down once we haven't touched it for a bit to give us a chance to move
        *msecondCounter = 0;
    }
}

void Game::handleDown(Uint32 *msecondCounter)
{
    // check if there is a piece below us blocking the way or the bottom of the screen
    // known bug: holding down the down arrow lets you go past the bottom
    bool blocked = false;
    std::vector<SDL_Rect> fallingRects = fallingPiece.getRects();

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect fallingRect = fallingRects[i];
        // get the absolute coords of the rects
        float fY = fallingPiece.getY() + fallingRect.y;
        float fX = fallingPiece.getX() + fallingRect.x;
        
        // get the grid coordinates
        int gridX = fX / BLOCK_SIZE;
        int gridY = fY / BLOCK_SIZE;

        if(gridY + 1 >= height / BLOCK_SIZE) {
            blocked = true;
            break;
        }
        if (grid[gridX][gridY + 1])
        {
            blocked = true;
            break;
        }
    }

    if (!blocked)
    {
        fallingPiece.setY(fallingPiece.getY() + BLOCK_SIZE);
        // The piece should only move down once we haven't touched it for a bit to give us a chance to move
        *msecondCounter = 0;
    }
}

void Game::handleRotate(Uint32 *msecondCounter)
{
    std::cout << "rotating" << std::endl;

    bool blocked = false;
    // TODO FIX
    if (!blocked)
    {
        // The piece should only move down once we haven't touched it for a bit to give us a chance to move
        *msecondCounter = 0;
        fallingPiece.rotateClockWise();
    }
}

void Game::handleEvents(Uint32 *msecondCounter)
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            handleLeft(msecondCounter);
            break;
        case SDLK_RIGHT:
            handleRight(msecondCounter);
            break;
        case SDLK_DOWN:
            handleDown(msecondCounter);
            break;
        // switch piece type for debugging
        case SDLK_1:
            if (I_tex != nullptr)
            {
                this->initPiece(I_tex, 1);
                std::cout << "changed piece to I" << std::endl;
            }
            break;

        case SDLK_2:
            if (Sq_tex != nullptr)
            {
                initPiece(Sq_tex, 2);
                std::cout << "changed piece to Sq" << std::endl;
            }
            break;

        case SDLK_3:
            if (LG_tex != nullptr)
            {
                initPiece(LG_tex, 3);
                std::cout << "changed piece to LG" << std::endl;
            }
            break;

        case SDLK_4:
            if (RG_tex != nullptr)
            {
                initPiece(RG_tex, 4);
                std::cout << "changed piece to RG" << std::endl;
            }
            break;

        case SDLK_5:
            if (LS_tex != nullptr)
            {
                initPiece(LS_tex, 5);
                std::cout << "changed piece to LS" << std::endl;
            }
            break;

        case SDLK_6:
            if (RS_tex != nullptr)
            {
                initPiece(RS_tex, 6);
                std::cout << "changed piece to RS" << std::endl;
            }
            break;

        case SDLK_7:
            if (T_tex != nullptr)
            {
                initPiece(T_tex, 7);
                std::cout << "changed piece to T" << std::endl;
            }
            break;

        case SDLK_r:
            handleRotate(msecondCounter);
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}

void Game::update(Uint32 *msecondCounter)
{
    //print debug
    
    bool collision = false;

    for (int j = 0; j < 4; j++)
    {
        SDL_Rect fallingRect = fallingPiece.getRects()[j];
        
        // get the absolute coords of the rects
        float fY = fallingPiece.getY() + fallingRect.y;
        float fX = fallingPiece.getX() + fallingRect.x;

        // get the grid coordinates
        int gridX = int(fX / BLOCK_SIZE);
        int gridY = int(fY / BLOCK_SIZE);

        if (gridY + 1 >= int(height / BLOCK_SIZE))
        {
            collision = true;
            break;
        }

        std::cout << "gridX: " << gridX << " gridY: " << gridY << grid.size() << std::endl;
        if (grid[gridX][gridY + 1])
        {
            std::cout << "hello" << std::endl;
            collision = true;
            break;
        }
    }

    if (!collision)
    {

        if (*msecondCounter >= constants::ADJUSTING_TIME)
        { // update pos once we have gone ADJUSTING_TIME ms without adjusting piece
            fallingPiece.setY(fallingPiece.getY() + BLOCK_SIZE);
            *msecondCounter = 0;
        }
    }
    else
    {
        // Add the falling piece to the stationary pieces
        if (*msecondCounter >= constants::ADJUSTING_TIME)
        { // give player last chance to move into small gap for example
            std::cout << "collided" << std::endl;
            
            // update the grid
            std::vector<SDL_Rect> fallingRects = fallingPiece.getRects();
            for (int i = 0; i < 4; i++)
            {
                SDL_Rect fallingRect = fallingRects[i];
                // get the absolute coords of the rects
                float fY = fallingPiece.getY() + fallingRect.y;
                float fX = fallingPiece.getX() + fallingRect.x;

                // get the grid coordinates
                int gridX = fX / BLOCK_SIZE;
                int gridY = fY / BLOCK_SIZE;

                grid[gridX][gridY] = true;
            }

            Piece oldFallingPiece = fallingPiece;
            stationaryPieces.push_back(oldFallingPiece);

            // Spawn a new piece
            SDL_Texture *tex = loadTexture("textures/I.png");
            initPiece(tex, 1);
            *msecondCounter = 0;
        }
    }
}

SDL_Texture *Game::loadTexture(const char *filePath)
{
    SDL_Texture *texture = nullptr;
    texture = IMG_LoadTexture(renderer, filePath);

    if (texture == nullptr)
    {
        std::cout << "Couldn't load texture" << std::endl;
    }
    return texture;
}


bool Game::running()
{
    return isRunning;
}

void Game::clear()
{
    SDL_RenderClear(renderer);
}

void Game::present()
{
    SDL_RenderPresent(renderer);
}

void Game::fillGridHelper(Bucket bucket) {
    std::vector<SDL_Rect> rects = bucket.getRects();
    for(SDL_Rect rect : rects) {
        // since bucket rects have varying sizes we first have to get width and height
        int width = rect.w;
        int height = rect.h;
        int x = rect.x;
        int y = rect.y;
        int col = int(x/BLOCK_SIZE);
        int row = int(y/BLOCK_SIZE);
        int numOfCols = int(width/BLOCK_SIZE);
        int numOfRows = int(height/BLOCK_SIZE);

        for(int i = 0; i < numOfRows; i++) {
            for(int j = 0; j < numOfCols; j++) {
                //print debug
                std::cout << "row: " << row + i << " col: " << col + j << std::endl;
                grid[col + j][row + i] = true;
            }
        }
    }

}


void Game::clearRows(std::vector<int> filledRows)
{
    
}

void Game::render(std::vector<Bucket> buckets)
{
    for (Bucket bucket : buckets)
    {
        std::vector<SDL_Rect> rects = bucket.getRects();
        SDL_Texture *texture = bucket.getTexture();

        for (SDL_Rect rect : rects)
        {
            SDL_Rect src;
            src.x = 0;
            src.y = 0;
            src.w = rect.w;
            src.h = rect.h;

            SDL_Rect dst = src;
            dst.x = rect.x;
            dst.y = rect.y;

            SDL_RenderCopy(renderer, texture, &src, &dst);
        }
    }
}

void Game::render(Piece piece)
{
    std::vector<SDL_Rect> rects = piece.getRects(); // the four blocks that make up our shape
    SDL_Texture *texture = piece.getTexture();

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect rect = rects[i];
        SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = rect.w;
        src.h = rect.h;

        SDL_Rect dst = src;
        dst.x = piece.getX() + rect.x; // Add the piece's x coordinate to the rect's x and y coordinate
        dst.y = piece.getY() + rect.y; // in rect.x and rect.y the relative coordinate to the first one is saved

        SDL_RenderCopy(renderer, texture, &src, &dst);
    }
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Quit" << std::endl;
}
