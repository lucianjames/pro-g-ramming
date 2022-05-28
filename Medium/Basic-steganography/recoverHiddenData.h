#pragma once
#include "readBinaryFile.h"
#include "getImageBits.h"
#include "bitsToImage.h"

void recoverHiddenData(std::string imagePath, std::string outputPath){
    // Load image
    std::cout << "Loading image..." << std::endl;
    cv::Mat image = cv::imread(imagePath);

    // Get the bits from the image
    std::vector<std::bitset<8>> imageBits = getImageBits(image);

    // Get the length of the data (read first 32 hidden bits)
    std::cout << "Reading hidden metadata..." << std::endl;
    std::bitset<32> hiddenDataLenBin;
    for(int bit = 0; bit < 32; bit++){
        hiddenDataLenBin[bit] = imageBits[bit][0];
    }

    // Get the actual data
    int dataLen = hiddenDataLenBin.to_ulong();
    std::cout << "Hidden data length according to hidden metadata: " << dataLen << std::endl;
    std::cout << "Reading hidden data from image..." << std::endl;
    std::vector<std::bitset<8>> dataBits;
    dataBits.resize(dataLen);
    int count = 32;
    for(int i = 0; i < dataLen; i++){
        for(int bit = 0; bit < 8; bit++){
            dataBits[i][bit] = imageBits[count][0];
            count++;
        }
    }

    // Write the bits to a file
    std::cout << "Writing hidden data to file..." << std::endl;
    std::ofstream file(outputPath, std::ios::binary);
    if(file.is_open()){
        for(int i = 0; i < dataBits.size(); i++){
            file << (char)dataBits[i].to_ulong();
        }
    }
    std::cout << outputPath << " written successfully!" << std::endl;
}