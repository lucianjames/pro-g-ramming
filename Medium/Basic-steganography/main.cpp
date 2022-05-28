// Easier to create a whole new file for this revision.
#include <opencv2/opencv.hpp>
#include <vector>
#include <bitset>
#include <iostream>
#include <fstream>
#include <filesystem>

void display_image(cv::Mat image){
    cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
    cv::imshow("Display Image", image);
    cv::waitKey(0);
}

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

void invalidArgs(){ // Because writing these couts twice is cringe
    std::cout << "Invalid arguments" << std::endl;
    std::cout << "Usage: ./main --hide <target_image> <data_file> <output_image_path>" << std::endl;
    std::cout << "Usage: ./main --recover <image_with_data> <output_data_path>" << std::endl;
}

// There are two ways to use this program:
// ./main --hide <target_image> <data_file> <output_image_path>
// ./main --recover <image_with_data> <output_data_path>
int main(int argc, char** argv){
    // Prevent segfault if no arguments are given:
    if(argc < 2){
        invalidArgs();
        return -1;
    }

    // Hide data in an image:
    if(strcmp(argv[1], "--hide") == 0){
        if(argc != 5){ // Check if the correct number of arguments are given
            invalidArgs();
            return -1;
        }
        // Verify that targetPath and dataPath are valid paths
        std::filesystem::path targetPathFSP(argv[2]);
        std::filesystem::path dataPathFSP(argv[3]);
        if(!std::filesystem::exists(targetPathFSP)){
            std::cout << "Error targetPath does not exist" << std::endl;
            return -1;
        }
        if(!std::filesystem::exists(dataPathFSP)){
            std::cout << "Error: dataPath does not exist" << std::endl;
            return -1;
        }
        std::string targetPath = argv[2];
        std::string dataPath = argv[3];
        std::string outputPath = argv[4];
        // Verify that outputPath ends in .png
        if(outputPath.length() < 4){
            std::cout << "Output image path must end in .png" << std::endl;
            return -1;
        }
        if(outputPath.substr(outputPath.size()-4, 4) != ".png"){ // This is a bit hacky, requires above length check to ensure a core dump doesnt happen
            std::cout << "Output image path must end in .png" << std::endl;
            return -1;
        }
        cv::Mat imageWithData = hideDataInImage(targetPath, dataPath);
        std::cout << "Writing image with hidden data to " << outputPath << std::endl;
        if(!cv::imwrite(outputPath, imageWithData)){
            std::cout << "Error: Could not write image to " << outputPath << std::endl;
            return -1;
        }else{
            std::cout << "Done!" << std::endl;
        }
    }

    // Recover hidden data from an image:
    else if(strcmp(argv[1], "--recover") == 0){
        // Verify that imagePath is a valid path:
        std::filesystem::path imagePathFSP(argv[2]);
        if(!std::filesystem::exists(imagePathFSP)){
            std::cout << "Error: imagePath does not exist" << std::endl;
            return -1;
        }
        // Do the recovery!:
        std::string imagePath = argv[2];
        std::string outputPath = argv[3];
        recoverHiddenData(imagePath, outputPath);
    }

    // Invalid arguments:
    else{
        invalidArgs();
        return -1;
    }

    return 0;
}