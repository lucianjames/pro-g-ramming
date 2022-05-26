#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>

#include "foodClass.h"
#include "snakeClass.h"

int main(){
    // Init ncurses
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE); // Don't wait for input

    // Create a window the size of the screen
    WINDOW* gameWindow = newwin(LINES, COLS, 0, 0);
    refresh();
    box(gameWindow, 0, 0);
    wrefresh(gameWindow);

    // Write the game title in the middle of the window
    mvwprintw(gameWindow, LINES/2, COLS/2 - 3, "Snake");
    wrefresh(gameWindow);
    usleep(1000000);

    // Create a snake object
    snakeClass Snake;

    // Create food
    foodClass Food(LINES*COLS/100);

    // Main game loop
    while(1){
        // Get input 
        Snake.getInput();

        // Update snake position and redraw it (update() does both)
        Snake.update(gameWindow, Food);

        // Draw all the food
        Food.drawFood(gameWindow);

        // Check for self collision
        Snake.checkForSelfCollision();

        // Check for food collision
        if(Food.checkEatFood(Snake.x, Snake.y)){
            Snake.length++;
            Snake.snakeXpreviousPositions.resize(Snake.length);
            Snake.snakeYpreviousPositions.resize(Snake.length);
        }

        // End game if snake is dead
        if(!Snake.alive){
            break;
        }

        // Wait for a bit
        usleep(100000);
    }

    // Show game over text
    refresh();
    box(gameWindow, 0, 0);
    wrefresh(gameWindow);
    mvwprintw(gameWindow, LINES/2, COLS/2 - 3, "Game over!");
    wrefresh(gameWindow);

    // Wait for a bit
    usleep(1000000);
    // Wait for user to press something
    nodelay(stdscr, FALSE);
    getch();

    // End ncurses
    endwin();
    return 0;
}