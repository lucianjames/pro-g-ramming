#include <iostream>
#include <fstream>
#include <sstream>

std::string LoadFileToString(const std::string& file_name) {
    std::ifstream file(file_name);
    if(file.is_open()) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        return buffer.str();
    }
    else{
        return "ERR_LOADING_FILE";
    }
    return "ERR";
}

int main(){

    // Pre-load all the files in /ASCII/ into an array of strings
    // Array formatted as so: [0,1,2,3,4,5,6,7,8,9,:]
    std::string characters[11];
    std::string filePath = "ASCII/";

    // Number load loop
    for(int i = 0; i < 10; i++){
        characters[i] = LoadFileToString(filePath + std::to_string(i));
    }
    // Load the colon
    characters[10] = LoadFileToString("ASCII/:");


    // Print all the characters for testing purposes
    for(int i = 0; i < 11; i++){
        std::cout << characters[i] << std::endl;
        std::cout << "----------------" << std::endl;
    }

    return 0;
}
