#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "../include/game.hpp"
#include "../include/constants.hpp"

SDL_Texture *I_tex;
SDL_Texture *Sq_tex;
SDL_Texture *LG_tex;
SDL_Texture *RG_tex;
SDL_Texture *LS_tex;
SDL_Texture *RS_tex;
SDL_Texture *T_tex;

int BLOCK_SIZE = constants::DEFAULT_BLOCK_SIZE;

void Game::init(const char *title, int x, int y, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Initialized";
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
    BLOCK_SIZE = 25;
    if (!I_tex || !Sq_tex || !LG_tex || !RG_tex || !LS_tex || !RS_tex || !T_tex)
    {
        std::cout << "Error loading textures!" << std::endl;
    }
}

void Game::initPiece(SDL_Texture *tex, int type)
{
    fallingPiece = Piece(width / 2, 0, 0, type, tex);
}

Piece Game::getFalling()
{
    return this->fallingPiece;
}

std::vector<Piece> Game::getStationary()
{
    return this->stationaryPieces;
};

void Game::handleLeft(Uint32 *msecondCounter)
{
    // check if there is a piece to the left of us blocking the way
    // or the edge of the screen
    bool blocked = false;

    SDL_Rect *fallingRects = fallingPiece.getRects();
    for (int i = 0; i < 4; i++)
    {
        SDL_Rect fallingRect = fallingRects[i];
        float fY = fallingPiece.getY() + fallingRect.y;
        float fX = fallingPiece.getY() + fallingRect.x;

        for (Piece piece : stationaryPieces)
        {
            SDL_Rect *stationaryRects = piece.getRects();
            for (int j = 0; j < 4; j++)
            {
                SDL_Rect stationaryRect = stationaryRects[j];
                float pX = piece.getX() + stationaryRect.x;
                float pY = piece.getY() + stationaryRect.y;
                float pH = stationaryRect.h;
                float pW = stationaryRect.w;

                if ((pY <= fY &&
                     fY < pY + pH &&
                     fX - BLOCK_SIZE < pX + pW) ||
                    fX - BLOCK_SIZE < 0)
                {
                    // Collision detected
                    blocked = true;
                    std::cout << "blocked" << std::endl;
                    break;
                }
            }

            if (blocked)
            {
                break;
            }
        }

        if (blocked)
        {
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
    SDL_Rect *fallingRects = fallingPiece.getRects();

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect fallingRect = fallingRects[i];
        // get the absolute coords of the rects
        float fY = fallingPiece.getY() + fallingRect.y;
        float fX = fallingPiece.getX() + fallingRect.x;
        float fW = fallingRect.w;

        for (Piece piece : stationaryPieces)
        {
            SDL_Rect *stationaryRects = piece.getRects();
            for (int j = 0; j < 4; j++)
            {
                SDL_Rect stationaryRect = stationaryRects[j];
                float pX = piece.getX() + stationaryRect.x;
                float pY = piece.getY() + stationaryRect.y;
                float pH = stationaryRect.h;

                if ((pY <= fY &&
                     fY < pY + pH &&
                     fX + fW + BLOCK_SIZE > pX) ||
                    fX + fW + BLOCK_SIZE > width)
                {
                    // Collision detected
                    blocked = true;
                    std::cout << "blocked" << std::endl;
                    break;
                }
            }

            if (blocked)
            {
                break;
            }
        }

        if (blocked)
        {
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
    // check if there is a piece to the right of us blocking the way
    // or the edge of the screen
    bool blocked = false;
    SDL_Rect *fallingRects = fallingPiece.getRects();

    for (int i = 0; i < 4; i++)
    {
        SDL_Rect fallingRect = fallingRects[i];
        // get the absolute coords of the rects
        float fY = fallingPiece.getY() + fallingRect.y;
        float fX = fallingPiece.getX() + fallingRect.x;
        float fW = fallingRect.w;
        float fH = fallingRect.h;

        for (Piece piece : stationaryPieces)
        {
            SDL_Rect *stationaryRects = piece.getRects();
            for (int j = 0; j < 4; j++)
            {
                SDL_Rect stationaryRect = stationaryRects[j];
                float pX = piece.getX() + stationaryRect.x;
                float pY = piece.getY() + stationaryRect.y;
                float pW = stationaryRect.w;

                if ((fY + fH >= pY &&
                     fX >= pX &&
                     fX + fW <= pX + pW) ||
                    fY + fH + BLOCK_SIZE >= height)
                {
                    // Collision detected
                    blocked = true;
                    std::cout << "blocked" << std::endl;
                    break;
                }
            }

            if (blocked)
            {
                break;
            }
        }

        if (blocked)
        {
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

    // Check if we are allowed to rotate
    bool blocked = false;
    std::array<int, 8> coords = fallingPiece.coordinatesOfCWRotation();
    for (int i = 0; i < 8; i += 2)
    {
        int x = fallingPiece.getX() + coords[i]; // Rect coords are defined as relative to the piece
        int y = fallingPiece.getY() + coords[i + 1];
        if (x < 0 || x >= width || y < 0 || y >= height)
        { // out of bounds
            std::cout << "rotation blocked: out of bounds" << std::endl;
            std::cout << "x: " << x << " y: " << y << std::endl;
            blocked = true;
            break;
        }

        for (Piece piece : stationaryPieces)
        {
            SDL_Rect *rects = piece.getRects();
            for (int j = 0; j < 4; j++)
            {
                SDL_Rect rect = rects[j];
                if (x >= piece.getX() + rect.x &&
                    x < piece.getX() + rect.x + rect.w &&
                    y >= piece.getY() + rect.y &&
                    y < piece.getY() + rect.y + rect.h)
                {
                    std::cout << "rotation blocked: piece in the way" << std::endl;
                    blocked = true;
                    break;
                }
            }
            if (blocked)
            {
                break;
            }
        }
    }
    if (!blocked)
    {
        fallingPiece.rotateClockWise();
    }
    // The piece should only move down once we haven't touched it for a bit to give us a chance to move
    *msecondCounter = 0;
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
    for (int i = 0; i < (int)stationaryPieces.size(); i++)
    {
        Piece piece = stationaryPieces[i];
        for (int j = 0; j < 4; j++)
        {
            SDL_Rect fallingRect = fallingPiece.getRects()[j];
            for (int k = 0; k < 4; k++)
            {
                SDL_Rect stationaryRect = piece.getRects()[k];
                // the x/y in rect is only relative to the piece so you have to add it to the x/y of the piece
                //  TODO clean this up
                if ((fallingPiece.getY() + fallingRect.y) + fallingRect.h + BLOCK_SIZE > (piece.getY() + stationaryRect.y) &&
                    !((fallingPiece.getY() + fallingRect.y) > (piece.getY() + stationaryRect.y) + stationaryRect.h - 1) &&
                    (fallingPiece.getX() + fallingRect.x) < (piece.getX() + stationaryRect.x) + stationaryRect.w &&
                    (fallingPiece.getX() + fallingRect.x) + fallingRect.w > (piece.getX() + stationaryRect.x))
                {
                    // Collision detected
                    collision = true;
                    break;
                }
            }
            if (collision)
                break;
        }
        if (collision)
            break;
    }

    bool bottomOfScreen = false;
    for (int i = 0; i < 4; i++)
    {
        // check if any of the squares of our piece touch the bottom edge of the screen
        SDL_Rect fallingRect = fallingPiece.getRects()[i];
        if (fallingPiece.getY() + fallingRect.y + BLOCK_SIZE >= height)
        {
            std::cout << "touched bottom" << std::endl;
            bottomOfScreen = true;
            break;
        }
    }

    if (!collision && !bottomOfScreen)
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

void Game::render(Piece piece)
{
    SDL_Rect *rects = piece.getRects(); // the four blocks that make up our shape
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
