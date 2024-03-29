#ifndef levelmaker_hpp
#define levelmaker_hpp

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class LevelMaker {

    public:
        LevelMaker(std::string filename);
        int calcNumberOfBuckets(std::vector<int> numbers);
        int getT();
        int getNumberOfBuckets();
        std::queue<int> createPieceVector();


    private:
        std::vector<int> numbers;
        int T;
        int numOfBuckets;
        
};
    


#endif 
