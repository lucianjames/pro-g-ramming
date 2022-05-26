#include <iostream>
#include <fstream>
#include <sstream>
#include <ncurses.h>
#include <unistd.h>

// prefer defines when used in functions because global variables are nasty
#define CHARHEIGHT 9
#define CHARWIDTH 12

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
    // clear window so there are no artifacts
    wclear(window);

    // Break the string into lines based on newline characters
    std::string charLines[CHARHEIGHT];
    std::stringstream ss(x);
    int i = 0;
    while(std::getline(ss, charLines[i])) {
        i++;
    }

    // Draw each line
    for(int i = 0; i < CHARHEIGHT; i++) {
        mvwprintw(window, i, 0, charLines[i].c_str());
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

    // Offset to center the clock
    int widthOffset = (COLS - CHARWIDTH*7) / 2;
    int heightOffset = (LINES - CHARHEIGHT) / 2;

    // Hours windows
    WINDOW *HoursL = newwin(CHARHEIGHT, CHARWIDTH, heightOffset, 0 + widthOffset);
    refresh();
    WINDOW *HoursR = newwin(CHARHEIGHT, CHARWIDTH, heightOffset, CHARWIDTH+1 + widthOffset);
    refresh();

    // Hours:Mins seperator window
    WINDOW *HoursMinsSep = newwin(CHARHEIGHT, CHARWIDTH/2, heightOffset, CHARWIDTH*2+2 + widthOffset);
    refresh();

    // Minutes windows
    WINDOW *MinsL = newwin(CHARHEIGHT, CHARWIDTH, heightOffset, CHARWIDTH*3+3 - CHARWIDTH/2 + widthOffset);
    refresh();
    WINDOW *MinsR = newwin(CHARHEIGHT, CHARWIDTH, heightOffset, CHARWIDTH*4+4 - CHARWIDTH/2 + widthOffset);
    refresh();

    // Mins:Seconds seperator window
    WINDOW *MinsSecSep = newwin(CHARHEIGHT, CHARWIDTH/2, heightOffset, CHARWIDTH*5+5 - CHARWIDTH/2 + widthOffset);
    refresh();

    // Seconds windows
    WINDOW *SecsL = newwin(CHARHEIGHT, CHARWIDTH, heightOffset, CHARWIDTH*5+6 + widthOffset);
    refresh();
    WINDOW *SecsR = newwin(CHARHEIGHT, CHARWIDTH, heightOffset, CHARWIDTH*6+7 + widthOffset);
    refresh();

    // Loop forever
    while (1)
    {
        // Get current time
        time_t now = time(0);
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
