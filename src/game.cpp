#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include <sstream>

#include "../include/game.hpp"
#include "../include/constants.hpp"
#include "../include/bucket.hpp"
#include "../include/level.hpp"

SDL_Texture *I_tex;
SDL_Texture *Sq_tex;
SDL_Texture *LG_tex;
SDL_Texture *RG_tex;
SDL_Texture *LS_tex;
SDL_Texture *RS_tex;
SDL_Texture *T_tex;
std::vector<SDL_Texture *> textures;


int BLOCK_SIZE = constants::DEFAULT_BLOCK_SIZE;

std::string Game::fieldToString(const Field& field) {
    std::stringstream ss;
    ss << "{" << field.x << "," << field.y << "," << field.w << "," << field.h << "," << field.occupied << "}";
    return ss.str();
}

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


    grid = std::vector<std::vector<Field>>(int(height/BLOCK_SIZE), std::vector<Field>(int(width/BLOCK_SIZE), {0,0,0,0,false,nullptr}));
}

void Game::initPiece(SDL_Texture *tex, int type)
{
    int center = (width / 2 / BLOCK_SIZE) * BLOCK_SIZE;
    fallingPiece = Piece(center, 0, 0, type, tex);
}

Piece Game::getFalling()
{
    return this->fallingPiece;
}


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
        if (grid[gridY][gridX - 1].occupied)
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
        if (grid[gridY][gridX + 1].occupied)
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
        if (grid[gridY + 1][gridX].occupied)
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
    bool blocked = false;
    
    std::array<int, 8> coords = fallingPiece.coordinatesOfCWRotation();
    for (int i = 0; i < 4; i++)
    {
        int x = fallingPiece.getX() + coords[i * 2];
        int y = fallingPiece.getY() + coords[i * 2 + 1];

        int gridX = x / BLOCK_SIZE;
        int gridY = y / BLOCK_SIZE;

        if (gridX < 0 || gridX >= width / BLOCK_SIZE || gridY < 0 || gridY >= height / BLOCK_SIZE)
        {
            blocked = true;
            break;
        }
        if (grid[gridY][gridX].occupied)
        {
            blocked = true;
            break;
        }
    }
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

        if (grid[gridY + 1][gridX].occupied)
        {
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

                grid[gridY][gridX] = {gridX * BLOCK_SIZE, gridY * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, true, fallingPiece.getTexture()};
            }

            // check if there are any rows that need clearing
            std::set<int> filledRows = whichLinesNeedClearing(grid, fallingPiece, BLOCK_SIZE);
            if(filledRows.size() > 0) {
                clearRows(&grid, filledRows);
            }

            // Spawn a new piece
            initPiece(I_tex, 1);
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
    else {
        textures.push_back(texture);
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

void Game::fillGridBorders(int width, int height, int numberOfBuckets) {
    int levelWidth = (numberOfBuckets + 1) * (4 * BLOCK_SIZE) ; // Each bucket is 4 blocks wide + the 4 block wide lock
    int paddingWidth = (width - levelWidth) / BLOCK_SIZE; // dividing by BLOCK_SIZE to get "grid coordinates"

    for(int i = 0; i < height / BLOCK_SIZE; i++) {
        for(int j = 0; j < paddingWidth / 2; j++) {
            grid[i][j] = {j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, true, nullptr};
        }
        for(int j = (width / BLOCK_SIZE) - (paddingWidth / 2); j < width / BLOCK_SIZE; j++) {
            grid[i][j] = {j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, true, nullptr};
        }
    }
    
}

void Game::fillGridHelper(Bucket bucket) {
    std::vector<SDL_Rect> rects = bucket.getRects();
    for(SDL_Rect rect : rects) {
        // since bucket rects have varying sizes we first have to get width and height
        grid[int(rect.y / BLOCK_SIZE)][int(rect.x / BLOCK_SIZE)] = {rect.x, rect.y, rect.w, rect.h, true, bucket.getTexture()};
    }
}

void Game::renderFalling(Piece piece)
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

void Game::renderAll(int width, int numberOfBuckets) {
    for(size_t i = 0; i < grid.size(); i++) {
        for(size_t j = 0; j < grid[i].size(); j++) {
            Field field = grid[i][j];
            SDL_Rect src;
            src.x = 0;
            src.y = 0;
            src.w = field.w;
            src.h = field.h;

            SDL_Rect dst = src;
            dst.x = field.x;
            dst.y = field.y;

            SDL_RenderCopy(renderer, field.texture, &src, &dst);
        }
    }

    if(height % BLOCK_SIZE != 0) {
        // in case the height is not a multiple of BLOCK_SIZE we have to render a border at the bottom
        SDL_Texture* border = loadTexture("textures/border_darkgray.png");

        SDL_Rect src;
        src.x = 0;
        src.y = 0;
        src.w = width;
        src.h = height % BLOCK_SIZE;

        SDL_Rect dst = src;
        dst.x = 0;
        dst.y = height - (height % BLOCK_SIZE);

        SDL_RenderCopy(renderer, border, &src, &dst);
        SDL_DestroyTexture(border);
    }
    // in case the width is not a multiple of BLOCK_SIZE we have to render a border at the right and left side
    // also we have to render a border incase the number of buckets is low and we want to center the level
    SDL_Texture* border = loadTexture("textures/border_darkgray.png");

    int levelWidth = (numberOfBuckets + 1) * (4 * BLOCK_SIZE) ; // Each bucket is 4 blocks wide + the 4 block wide lock
    int paddingWidth = width - levelWidth;
    int sidePadding = (paddingWidth / 2) - ((paddingWidth / 2) % BLOCK_SIZE);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = sidePadding;
    src.h = height;
    SDL_Rect dst = src;

    SDL_RenderCopy(renderer, border, &src, &dst);
    
    src.x = width - sidePadding;
    dst = src;
    SDL_RenderCopy(renderer, border, &src, &dst);
    SDL_DestroyTexture(border);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    for(SDL_Texture* texture : textures) {
        SDL_DestroyTexture(texture);
    }
    SDL_Quit();
    std::cout << "Game Quit" << std::endl;
}
