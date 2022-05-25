#include <iostream>
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include<unistd.h>

// prefer defines when used in functions because global variables are nasty
#define CHARHEIGHT 13
#define CHARWIDTH 13

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

void WriteInWindow(std::string x, WINDOW* window){
    wclear(window); // clear window so there are no artifacts
    // Break the string into lines based on newline characters
    std::string charLines[CHARHEIGHT];
    std::stringstream ss(x);
    int i = 0;
    while(std::getline(ss, charLines[i])) {
        i++;
    }
    // Draw each line
    for(int i = 0; i < CHARHEIGHT; i++) {
        mvwprintw(window, i+1, 1, charLines[i].c_str()); //Offset because box
    }
    // Refresh the window
    wrefresh(window);
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


    // NCURSES TIME!!!
    initscr(); // sets up memory and clears the screen
    noecho(); // don't echo the characters to the screen
    curs_set(0); // hide the cursor

    // Hours windows
    WINDOW *HoursL = newwin(CHARHEIGHT, CHARWIDTH, 0, 0);
    refresh();
    WINDOW *HoursR = newwin(CHARHEIGHT, CHARWIDTH, 0, CHARWIDTH+1);
    refresh();

    // Hours:Mins seperator window
    WINDOW *HoursMinsSep = newwin(CHARHEIGHT, CHARWIDTH/2, 0, CHARWIDTH*2+2);
    refresh();

    // Minutes windows
    WINDOW *MinsL = newwin(CHARHEIGHT, CHARWIDTH, 0, CHARWIDTH*3+3 - CHARWIDTH/2);
    refresh();
    WINDOW *MinsR = newwin(CHARHEIGHT, CHARWIDTH, 0, CHARWIDTH*4+4 - CHARWIDTH/2);
    refresh();

    // Mins:Seconds seperator window
    WINDOW *MinsSecSep = newwin(CHARHEIGHT, CHARWIDTH/2, 0, CHARWIDTH*5+5 - CHARWIDTH/2);
    refresh();

    // Seconds windows
    WINDOW *SecsL = newwin(CHARHEIGHT, CHARWIDTH, 0, CHARWIDTH*5+6);
    refresh();
    WINDOW *SecsR = newwin(CHARHEIGHT, CHARWIDTH, 0, CHARWIDTH*6+7);
    refresh();

    // Loop forever
    while (1)
    {
        // Get current time
        time_t now = time(0);
        // Get seconds
        tm *ltm = localtime(&now);
        // Get the hours
        int hours = ltm->tm_hour;
        // Get the minutes
        int minutes = ltm->tm_min;
        // Get the seconds
        int seconds = ltm->tm_sec;

        // Clear the screen
        clear();
        refresh();

        // Draw the seperators
        WriteInWindow(characters[10], HoursMinsSep);
        WriteInWindow(characters[10], MinsSecSep);

        // Write the hours
        WriteInWindow(characters[hours/10], HoursL);
        WriteInWindow(characters[hours%10], HoursR);

        // Write the minutes
        WriteInWindow(characters[minutes/10], MinsL);
        WriteInWindow(characters[minutes%10], MinsR);

        // Write seconds
        WriteInWindow(characters[seconds/10], SecsL);
        WriteInWindow(characters[seconds%10], SecsR);

        // Wait for a tenth of a second
        usleep(100000);
    }    

    endwin(); // dealloc memory and ends ncurses
    return 0;
}
