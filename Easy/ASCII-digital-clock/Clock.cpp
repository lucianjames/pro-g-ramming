#include <iostream>
#include <fstream>
#include <sstream>
#include <ncurses.h>

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
    for(int i = 0; i < 10; i++){
        characters[i] = LoadFileToString(filePath + std::to_string(i));
    }
    characters[10] = LoadFileToString("ASCII/:");
    int charheight = 13;
    int charwidth = 13;


    // NCURSES TIME!!!
    initscr(); // sets up memory and clears the screen
    noecho(); // don't echo the characters to the screen
    curs_set(0); // hide the cursor

    // Loop time! This displays all the characters one at a time
    for(int i=0; i<11; i++){
        // Clear the screen
        clear();
        // Create a window for the character of size charheight x charwidth
        WINDOW *charwin = newwin(charheight, charwidth, 0, 0);
        refresh();
        box(charwin, 0, 0);
        
        // Break the string into lines based on newline characters
        std::string charLines[charheight];
        std::stringstream ss(characters[i]);
        int lineCount = 0;
        while(std::getline(ss, charLines[lineCount])){
            lineCount++;
        }

        // Draw each line
        for(int l=0; l<charheight-1; l++){
            mvwprintw(charwin, l+1, 1, charLines[l].c_str());
        }
        // Refresh the window
        wrefresh(charwin);
        // Wait for input
        getch();
    }
    endwin(); // dealloc memory and ends ncurses
    return 0;
}
