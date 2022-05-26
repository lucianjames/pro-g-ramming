#include <ncurses.h>
#include <vector>
#include <string>

class snakeClass{
private:
    int input = -1;

public:
    std::vector<int> snakeXpreviousPositions;
    std::vector<int> snakeYpreviousPositions;
    bool alive = true;
    int x = LINES/2;
    int y = COLS/2;
    int length = 2;
    int direction = 0;
    char headChar[2] = "@";
    char bodyChar[2] = "#";


    snakeClass(){ // Constructor
        snakeXpreviousPositions.resize(length);
        snakeYpreviousPositions.resize(length);
        snakeXpreviousPositions[0] = x;
        snakeYpreviousPositions[0] = y;
    }


    void getInput(){
        int getchInput = getch();
        if(getchInput != -1 && getchInput != this->input){ // If the input is different from the previous input and not -1
            this->input = getchInput; // Set the input to the new input
        }
        // Set direction using a case
        switch(this->input){
            case 'W': // Fall-through
            case 'w':
                if(this->direction != 2){this->direction = 0;} // If the snake is not moving down, set direction to 0 (up)
                break;
            case 'D': // Fall-through
            case 'd':
                if(this->direction != 3){this->direction = 1;} // If the snake is not moving left, set direction to 1 (right)
                break;
            case 'S': // Fall-through
            case 's':
                if(this->direction != 0){this->direction = 2;} // If the snake is not moving up, set direction to 2 (down)
                break;
            case 'A': // Fall-through
            case 'a':
                if(this->direction != 1){this->direction = 3;} // If the snake is not moving right, set direction to 3 (left)
                break;
        }
    }


    void checkForSelfCollision(){
        for(int i = 0; i < this->length-1; i++){
            if(this->x == this->snakeXpreviousPositions[i] && this->y == this->snakeYpreviousPositions[i]){ // If the snake is at the same position as any of the stored previous positions
                this->alive = false; // Kill the snake :)
            }
        }
    }


    void update(WINDOW* window, foodClass& Food){
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

        // Add new positions to the vectors
        snakeXpreviousPositions.push_back(this->x);
        snakeYpreviousPositions.push_back(this->y);

        // Pop the first element of the vector if the vector is longer than the snake length
        if(snakeXpreviousPositions.size() > this->length){ // If the vector is longer than the snake length
            snakeXpreviousPositions.erase(snakeXpreviousPositions.begin()); // Erase the first element
            snakeYpreviousPositions.erase(snakeYpreviousPositions.begin()); // Erase the first element
        }

        // Draw the snakes head
        mvwaddch(window, this->x, this->y, this->headChar[0]);
        // Draw the snakes body
        for(int i = 0; i < snakeXpreviousPositions.size()-1; i++){ // Loop through the vector of previous positions
            mvwaddch(window, snakeXpreviousPositions[i], snakeYpreviousPositions[i], this->bodyChar[0]); // Draw the body part at the previous position i
        }

        // Refresh the window
        wrefresh(window);
    }


    void eat(foodClass& Food){
        if(Food.checkEatFood(this->x, this->y)){ // If the snake ate the food
            this->length++; // Increase the snake length
            this->snakeXpreviousPositions.resize(this->length); // Resize the previous positions vectors
            this->snakeYpreviousPositions.resize(this->length); // Resize the previous positions vectors
            this->snakeXpreviousPositions[this->length-1] = -1; // Set the last x position to -1 to hide it until the next update
            this->snakeYpreviousPositions[this->length-1] = -1; // Set the last y position to -1 to hide it until the next update
        }
    }
};
