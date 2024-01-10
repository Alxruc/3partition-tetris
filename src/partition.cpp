#include "../include/partition.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>

int calcNumberOfBuckets(std::vector<int> numbers) {
    int numOfElements = numbers.size();
    if(numOfElements % 3 != 0) {
        std::cout << "The number of elements in the vector must be divisible by 3" << std::endl;
        return -1;
    } else {
        int numOfBuckets = numOfElements / 3;
        return numOfBuckets;
    }
}





