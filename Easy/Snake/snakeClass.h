#include <ncurses.h>
#include <unistd.h>
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
                if(this->direction != 2){this->direction = 0;}
                break;
            case 'D': // Fall-through
            case 'd':
                if(this->direction != 3){this->direction = 1;}
                break;
            case 'S': // Fall-through
            case 's':
                if(this->direction != 0){this->direction = 2;}
                break;
            case 'A': // Fall-through
            case 'a':
                if(this->direction != 1){this->direction = 3;}
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

    void update(WINDOW* window, foodClass Food){
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

        // Refresh the window
        wrefresh(window);
    }
};
