#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <bitset>

// Convert a cv::Mat into a vector of 8-bit sets. Assumes RGB image.
std::vector<std::bitset<8>> getImageBits(cv::Mat m){
    std::vector<std::bitset<8>> bits;
    for(int i = 0; i < m.rows; i++){
        for(int j = 0; j < m.cols*3; j++){ // Multiply cols by 3 because of the 3 channels (could add a third loop but this is easier)
            bits.push_back(m.at<uchar>(i,j));
        }
    }
    return bits;
}