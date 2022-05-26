#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include <string>

struct food {
    int x;
    int y;
};

// Food class contains all the foods positions
class foodClass{
private:
    std::vector<food> foodPositions;
public:
    
    void addFoodRndPos(){
        food foodPos;
        foodPos.x = rand() % (COLS - 2) + 1;
        foodPos.y = rand() % (LINES - 2) + 1;
        foodPositions.push_back(foodPos);
    }

    // Return true if food at position
    bool CheckEatFood(int x, int y){
        for(int i = 0; i < foodPositions.size(); i++){
            if(foodPositions[i].x == x && foodPositions[i].y == y){
                // Remove food from vector
                foodPositions.erase(foodPositions.begin() + i);
                return true;
            }
        }
        return false;
    }

    void drawFood(WINDOW* window){
        for(int i = 0; i < foodPositions.size(); i++){
            mvwaddch(window, foodPositions[i].y, foodPositions[i].x, '*');
        }
        wrefresh(window);
    }
};

class snakeClass{
private:
    int input = -1;
    std::vector<int> snakeXpreviousPositions;
    std::vector<int> snakeYpreviousPositions;
public:
    bool alive = true;
    int x = LINES/2;
    int y = COLS/2;
    int length = 2;
    int direction = 0;
    char headChar[2] = "@";
    char bodyChar[2] = "#";

    snakeClass(){
        snakeXpreviousPositions.resize(length);
        snakeYpreviousPositions.resize(length);
        snakeXpreviousPositions[0] = x;
        snakeYpreviousPositions[0] = y;
    }

    void getInput(){
        int getchInput = getch();
        if(getchInput != -1 && getchInput != this->input){
            this->input = getchInput;
        }
        // Set direction using a case
        switch(this->input){
            case 'W': // Fall-through
            case 'w':
                this->direction = 0;
                break;
            case 'D': // Fall-through
            case 'd':
                this->direction = 1;
                break;
            case 'S': // Fall-through
            case 's':
                this->direction = 2;
                break;
            case 'A': // Fall-through
            case 'a':
                this->direction = 3;
                break;
        }
    }

    void checkForSelfCollision(){
        for(int i = 0; i < this->length-1; i++){
            if(this->x == this->snakeXpreviousPositions[i] && this->y == this->snakeYpreviousPositions[i]){
                this->alive = false;
            }
        }
    }

    void update(WINDOW* window, foodClass food){
        wclear(window); // Clear the window
        // Update position based on direction
        switch(this->direction){
            case 0: // Up
                this->x--;
                break;
            case 1: // Right
                this->y++;
                break;
            case 2: // Down
                this->x++;
                break;
            case 3: // Left
                this->y--;
                break;
        }

        // Loop around if snake goes off screen (account for the fact the box takes up 1 extra space)
        if(this->x < 0){
            this->x = LINES-1;    
        }
        if(this->x > LINES-1){
            this->x = 0;
        }
        if(this->y < 0){
            this->y = COLS-1;
        }
        if(this->y > COLS-1){
            this->y = 0;
        }


        // Add new position to the vector
        snakeXpreviousPositions.push_back(this->x);
        snakeYpreviousPositions.push_back(this->y);

        // Pop the first element of the vector if the vector is longer than the snake length
        if(snakeXpreviousPositions.size() > this->length){
            snakeXpreviousPositions.erase(snakeXpreviousPositions.begin());
            snakeYpreviousPositions.erase(snakeYpreviousPositions.begin());
        }

        // Draw the snakes head
        mvwaddch(window, this->x, this->y, this->headChar[0]);
        // Draw the snakes body
        for(int i = 0; i < snakeXpreviousPositions.size()-1; i++){
            mvwaddch(window, snakeXpreviousPositions[i], snakeYpreviousPositions[i], this->bodyChar[0]);
        }

        // Try and eat food on the head position
        if(food.CheckEatFood(this->x, this->y)){
            this->length++;
            food.addFoodRndPos();
        }

        // Refresh the window
        wrefresh(window);
    }
};

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
    foodClass Food;

    // Create some food
    for(int i=0; i<100; i++){
        Food.addFoodRndPos();
    }

    // Main game loop
    while(1){
        // Get input 
        Snake.getInput();
        
        // Write input into window for test purposes
        mvwprintw(gameWindow, 0, 0, "%d", Snake.direction);

        // Update snake position and redraw it (update() does both)
        Snake.update(gameWindow, Food);
        Food.drawFood(gameWindow);

        // Check for self collision
        Snake.checkForSelfCollision();
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