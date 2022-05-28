#include <opencv2/opencv.hpp>
#include <vector>
#include <bitset>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "hideDataInImage.h"
#include "recoverHiddenData.h"

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