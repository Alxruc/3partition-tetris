#include "../include/levelmaker.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>
#include <vector>
#include <fstream> 
#include <string>
#include <sstream>
#include <unistd.h>

LevelMaker::LevelMaker(std::string filename) { 
    std::string filePath = "./partitionLevels/" + filename;
    std::ifstream inputfile(filePath);

    if (!inputfile) {
        std::cerr << "Unable to open file " << filePath << std::endl;
    }
    else {

        int number;
        std::string line;
        // Read the first line (all the integers)
        if (std::getline(inputfile, line)) {
            std::istringstream iss(line);
            while (iss >> number) {
                numbers.push_back(number);
            }
        }

        // Read the second line (our T)
        if (std::getline(inputfile, line)) {
            std::istringstream iss(line);
            if (!(iss >> T)) {
                std::cerr << "Error reading T" << std::endl;
            }
        }
    }

    numOfBuckets = calcNumberOfBuckets(numbers);
}



int LevelMaker::calcNumberOfBuckets(std::vector<int> numbers) {
    int numOfElements = numbers.size();
    if(numOfElements % 3 != 0) {
        std::cout << "The number of elements in the vector must be divisible by 3" << std::endl;
        return -1;
    } else {
        int numOfBuckets = numOfElements / 3;
        return numOfBuckets;
    }
}

int LevelMaker::getT() {
    return T;
}

int LevelMaker::getNumberOfBuckets() {
    return numOfBuckets;
}




