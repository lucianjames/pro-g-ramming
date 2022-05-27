// Basic steganography using openCV
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>

/*

!!!!!!!!!!!!!!!!!!!
This code is awful right now, just a proof of concept.
!!!!!!!!!!!!!!!!!!!

*/

void display_image(cv::Mat image){
    cv::namedWindow("Display Image", cv::WINDOW_NORMAL);
    cv::imshow("Display Image", image);
    cv::waitKey(0);
}

std::vector<std::bitset<8>> imageBits(cv::Mat m){
    std::vector<std::bitset<8>> bits;
    for(int i = 0; i < m.rows; i++){
        for(int j = 0; j < m.cols*3; j++){ // Multiply cols by 3 because of the 3 channels (could add a third loop but this is easier)
            bits.push_back(m.at<uchar>(i,j));
        }
    }
    return bits;
}

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

int main(){

    // Get the data that needs to be hidden
    cv::Mat image_to_hide = cv::imread("testImages/toHide.png");
    std::vector<std::bitset<8>> image_to_hide_bits = imageBits(image_to_hide);
    // Calculate the number of bits that will be hidden
    int num_bits_to_hide = image_to_hide_bits.size()*8;
    std::cout << "Number of bits to hide: " << num_bits_to_hide << std::endl;

    // Load the target image
    cv::Mat target_image = cv::imread("testImages/target.png");
    std::vector<std::bitset<8>> target_image_bits = imageBits(target_image);
    // Calculate the number of bits available given only the last bit of each pixel
    int num_bits_available = target_image_bits.size();
    std::cout << "Number of bits available: " << num_bits_available << std::endl;

    // Check if there is enough space to hide the data
    if(num_bits_to_hide > num_bits_available){
        std::cout << "Not enough space to hide the data" << std::endl;
        return 0;
    }


    // Display image before modification
    std::cout << "Image before modification" << std::endl;
    display_image(target_image);

    // Hide the data
    // Add some "metadata" to the image first
    int count = 0;

    // Add the number of rows and cols in the hidden image as 16-bit numbers (short int)
    std::bitset<16> nRows = image_to_hide.rows;
    std::bitset<16> nCols = image_to_hide.cols;

    for(int bit=0 ; bit < 8; bit++){
        target_image_bits[count][0] = nRows[bit];
        count++;
    }
    for(int bit=0 ; bit < 8; bit++){
        target_image_bits[count][0] = nCols[bit];
        count++;
    }

    for(int i = 0; i < image_to_hide_bits.size(); i++){
        for(int bit=0; bit<8; bit++){
            target_image_bits[count][0] = image_to_hide_bits[i][bit];
            count++;
        }
    }

    // Convert the bits back to an image
    cv::Mat new_image = bitsToImage(target_image_bits, target_image.rows, target_image.cols);

    // Display the new image
    std::cout << "Image after hiding the data" << std::endl;
    display_image(new_image);


    // Time to try and recover the data!
    // Convert new_image to a vector of bits
    std::vector<std::bitset<8>> new_image_bits = imageBits(new_image);

    // Get the number of rows and cols from the new image
    std::bitset<16> nRows_new = 0;
    std::bitset<16> nCols_new = 0;
    for(int bit=0 ; bit < 8; bit++){
        nRows_new[bit] = new_image_bits[bit][0];
    }
    for(int bit=0 ; bit < 8; bit++){
        nCols_new[bit] = new_image_bits[bit+8][0];
    }
    std::cout << "Number of rows detected from hidden metadata: " << nRows_new.to_ulong() << std::endl;
    std::cout << "Number of cols detected from hidden metadata: " << nCols_new.to_ulong() << std::endl;
    int nRowsInHidden = nRows_new.to_ulong();
    int nColsInHidden = nCols_new.to_ulong();

    // Get the data from the new image
    std::vector<std::bitset<8>> recovered_image_data;
    recovered_image_data.resize(nRows_new.to_ulong()*nCols_new.to_ulong()*3);
    int recoverycount = 16;
    for(int i=0; i<nRowsInHidden*nColsInHidden*3; i++){
        for(int bit=0; bit<8; bit++){
            recovered_image_data[i][bit] = new_image_bits[recoverycount][0];
            recoverycount++;
        }
    }

    cv::Mat recovered_image = bitsToImage(recovered_image_data, nRows_new.to_ulong(), nCols_new.to_ulong());
    std::cout << "Recovered data" << std::endl;
    display_image(recovered_image);


    // Save the new image with the hidden data
    cv::imwrite("testImages/newImage.png", new_image);

    return 0;
}