#pragma once
#include "readBinaryFile.h"
#include "getImageBits.h"
#include "bitsToImage.h"

// Overwrites the least significant bit of pixels
cv::Mat hideDataInImage(std::string targetPath, std::string dataPath){
    // Get binary data from a file
    std::vector<std::bitset<8>> toHideBits = readBinaryFile(dataPath);

    // Load target image
    std::cout << "Loading target image..." << std::endl;
    cv::Mat targetImage = cv::imread(targetPath);

    // Convert target image to bits
    std::cout << "Converting target image cv::Mat to bitsets..." << std::endl;
    std::vector<std::bitset<8>> targetImageBits = getImageBits(targetImage);

    std::cout << "Number of LSBs to hide in: " << targetImageBits.size() << std::endl;
    std::cout << "Hidden data length: " << toHideBits.size() << std::endl;
    if(toHideBits.size() > targetImageBits.size()){
        std::cout << "Error: Data too big for image!" << std::endl;
        std::cout << "!!!!Returning original image!!!!" << std::endl;
        return targetImage;
    }
    
    // Add the length of toHideBits*8 to the first few LSB bits of each pixel
    std::cout << "Adding hidden metadata..." << std::endl;
    std::bitset<32> hiddenDataLenBin = toHideBits.size();
    int count = 0;
    for(int bit=0 ; bit < 32; bit++){
        targetImageBits[count][0] = hiddenDataLenBin[bit];
        count++;
    }

    // Add the actual data to the image
    std::cout << "Adding hidden data..." << std::endl;
    for(int i = 0; i < toHideBits.size(); i++){
        for(int bit = 0; bit < 8; bit++){
            targetImageBits[count][0] = toHideBits[i][bit];
            count++;
        }
    }

    // Convert the bits back into an image
    std::cout << "Converting bitsets back into a cv::Mat..." << std::endl;
    cv::Mat imageWithData = bitsToImage(targetImageBits, targetImage.rows, targetImage.cols);
    return imageWithData;
}
