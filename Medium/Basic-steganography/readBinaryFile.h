#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <bitset>

// Read any binary file into a vector of bits
std::vector<std::bitset<8>> readBinaryFile(std::string file_name){
    std::vector<std::bitset<8>> bits;
    std::ifstream file(file_name, std::ios::binary);
    if(file.is_open()){
        char c;
        while(file.get(c)){
            bits.push_back(std::bitset<8>(c));
        }
    }
    return bits;
}