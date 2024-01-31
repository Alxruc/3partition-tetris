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

std::queue<int> LevelMaker::createPieceVector() {
    std::queue<int> pieceVector;
    for(size_t i = 0; i < numbers.size(); i++) {
        // Initiator 
        pieceVector.push(4); //RG
        
        // Filler
        for(int j = 0; j < numbers[i]; j++) {
            pieceVector.push(2); //Sq
            pieceVector.push(3); //LG
            pieceVector.push(2); //Sq
        }

        // Terminator
        pieceVector.push(2);
        pieceVector.push(1);
    }
    // Filling the buckets
    for(size_t i = 0; i < numbers.size()/3; i++) {
        pieceVector.push(4); //RG 
    }
    pieceVector.push(7); //T
    for(int i = 0; i < (5*T + 16) / 4; i++) {
        pieceVector.push(1); //I
    }
    return pieceVector;
}

int LevelMaker::getT() {
    return T;
}

int LevelMaker::getNumberOfBuckets() {
    return numOfBuckets;
}




