#include <ncurses.h>

// Colour defines for ncurses 
#define GREENBLACK 1
#define REDBLACK 2
#define YELLOWBLACK 3
#define BLUEBLACK 4
#define MAGENTABLACK 5
#define CYANBLACK 6
#define WHITEBLACK 7

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
    WINDOW *tetris_win = newwin(50, 30, (LINES - 50) / 2, (COLS - 30) / 2);
    refresh();

    // Test all the colours in the tetris window
    for(int i = 1; i < 7; i++){
        wattron(tetris_win, COLOR_PAIR(i));
        mvwprintw(tetris_win, i, 1, "Hello World");
        wattroff(tetris_win, COLOR_PAIR(i));
    }
    box(tetris_win, 0, 0);
    wrefresh(tetris_win);

    // Wait for input
    getch();

    // End ncurses
    endwin();
    return 0;
}