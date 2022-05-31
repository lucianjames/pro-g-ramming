#include <ncurses.h>
#include <vector> // vectors are just easier to work with than arrays
#include <unistd.h>

#include "blocks.h"

// Colour defines for ncurses 
#define GREENBLACK 1
#define REDBLACK 2
#define YELLOWBLACK 3
#define BLUEBLACK 4
#define MAGENTABLACK 5
#define CYANBLACK 6
#define WHITEBLACK 7

class block{
public:
    // Shape of the block
    std::vector<std::vector<int>> shape;
    // Position of the block
    int x = 1; // Account for the border
    int y = 1; // Account for the border
    // Colour of the block
    int colourPair;
    // Block rotation
    int rotation;

    block(){
        // All this init is just for testing purposes
        this->shape = block_S;
        this->colourPair = GREENBLACK;
    }

    void draw(WINDOW *win){
        // Enable colourpair attribute
        wattron(win, COLOR_PAIR(this->colourPair));
        // Draw the block
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                if(this->shape[i][j] == 1){
                    mvwaddch(win, this->y + i, this->x + j, '#');
                }
            }
        }
        // Disable colourpair attribute
        wattroff(win, COLOR_PAIR(this->colourPair));
        // Refresh the window
        wrefresh(win);
    }

    void tick(){
        // Move the block down one row
        if(this->y < 20-4){
            this->y++;
        }
    }

};


int main(){
    // ==========Initial setup========== //
    initscr(); // Initialize ncurses
    noecho(); // Don't echo input
    curs_set(0); // Hide the cursor
    start_color(); // Initialize colors
    init_pair(1, COLOR_GREEN, COLOR_BLACK); // Green colour pair
    init_pair(2, COLOR_RED, COLOR_BLACK); // Red colour pair
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); // Yellow colour pair
    init_pair(4, COLOR_BLUE, COLOR_BLACK); // Blue colour pair
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK); // Magenta colour pair
    init_pair(6, COLOR_CYAN, COLOR_BLACK); // Cyan colour pair
    init_pair(7, COLOR_WHITE, COLOR_BLACK); // White colour pair
    // ================================= //


    // ==========Game setup========== //
    int score = 0; // Initial score
    // Define tetris window in middle of screen (fixed size)
    WINDOW *tetris_win = newwin(20, 20, (LINES - 20) / 2, (COLS - 20) / 2);
    refresh();

    block testBlock;

    block testBlock2;
    testBlock2.shape = block_O;
    testBlock2.colourPair = REDBLACK;
    testBlock2.x = 5;
    testBlock2.y = 5;
    // ================================= //

    // ==========Game loop========== //
    while(true){
        // Move the blocks down
        testBlock.tick();
        testBlock2.tick();

        // Clear screen
        wclear(tetris_win);

        // Render blocks
        testBlock.draw(tetris_win);
        testBlock2.draw(tetris_win);
        box(tetris_win, 0, 0); // Draw a box around the window
        wrefresh(tetris_win); // Refresh the window

        // Wait
        usleep(100000);
    }

    // Wait for input
    getch();


    // End ncurses
    endwin();
    return 0;
}