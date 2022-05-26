#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "foodClass.h"
#include "snakeClass.h"

int main(){
    // ==========Initial setup========== //
    initscr(); // Initialize ncurses
    noecho(); // Don't echo input
    curs_set(0); // Hide the cursor
    nodelay(stdscr, TRUE); // Don't wait for input
    WINDOW* gameWindow = newwin(LINES, COLS, 0, 0); // Create a new window for the game
    refresh();
    box(gameWindow, 0, 0); // Draw a box around the window
    wrefresh(gameWindow); // Refresh the window
    snakeClass Snake; // Create a snake object
    foodClass Food(LINES*COLS/100); // Create food. 1% of the screen is food
    // ================================= //



    // ==========Title screen=========== //
    mvwprintw(gameWindow, LINES/2, COLS/2 - 5, "~~Snake~~"); // Write the game title in the middle of the window
    mvwprintw(gameWindow, LINES/2 + 1, COLS/2 - 10, "Use W,A,S,D to move"); // Write instructions
    mvwprintw(gameWindow, LINES/2 + 2, COLS/2 - 11, "Press any key to start");
    wrefresh(gameWindow);
    nodelay(stdscr, FALSE); // Wait for input
    int input = getch();
    nodelay(stdscr, TRUE); // Dont wait for input
    // ================================= //



    // ==========Game loop============== //
    while(1){
        Snake.getInput(); // Get input 
        Snake.update(gameWindow, Food); // Update snake position and redraw it (update() does both)
        Food.drawFood(gameWindow); // Draw all the food
        Snake.checkForSelfCollision(); // Check for self collision
        // Check for food collision:
        Snake.eat(Food);
        // End game if snake is dead:
        if(!Snake.alive){ 
            break;
        }
        usleep(100000); // Wait for a bit
    }
    // ================================= //



    // ==========Game over============== //
    refresh();
    box(gameWindow, 0, 0);
    wrefresh(gameWindow);
    mvwprintw(gameWindow, LINES/2, COLS/2 - 5, "Game over!");
    mvwprintw(gameWindow, LINES/2 + 1, COLS/2 - 7, "Your score: %d", Snake.length);
    wrefresh(gameWindow);
    usleep(2000000); // Wait for a bit
    mvwprintw(gameWindow, LINES/2 + 2, COLS/2 - 11, "Press any key to exit..");
    wrefresh(gameWindow);
    nodelay(stdscr, FALSE);
    getch(); // Wait for user to press something
    // ================================= //



    // ===========Cleanup=============== //
    endwin();
    return 0;
}