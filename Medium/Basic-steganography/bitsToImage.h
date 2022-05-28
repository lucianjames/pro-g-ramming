#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <bitset>

// Convert a vector of 8-bit sets into a cv::Mat.
cv::Mat bitsToImage(std::vector<std::bitset<8>> bits, int rows, int cols){
    cv::Mat m(rows, cols, CV_8UC3);
    int count = 0;
    for(int i = 0; i < m.rows; i++){
        for(int j = 0; j < m.cols*3; j++){ // Multiply cols by 3 because of the 3 channels (could add a third loop but this is easier)
            m.at<uchar>(i,j) = bits[count].to_ulong();
            count++;
        }
    }
    return m;
}