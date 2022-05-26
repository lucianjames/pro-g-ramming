#include <ncurses.h>
#include <vector>

// Struct to hold food coordinates and char
struct foodStruct{
    int x;
    int y;
    char foodChar[2] = "*"; // What to draw for food
};


class foodClass{
public:
    std::vector<foodStruct> foodVector; // Vector to hold all the food objects


    foodClass(int n){ // Constructor
        this->foodVector.resize(n); // Resize the vector to n food objects
        for(int i = 0; i < this->foodVector.size(); i++){ // For each food object
            this->foodVector[i].x = rand() % LINES; // Set x coordinate to a random number between 0 and LINES
            this->foodVector[i].y = rand() % COLS; // Set y coordinate to a random number between 0 and COLS
        }
    }


    void drawFood(WINDOW* window){ // Draw all the food
        for(int i = 0; i < this->foodVector.size(); i++){ // For each food object
            mvwprintw(window, this->foodVector[i].x, this->foodVector[i].y, this->foodVector[i].foodChar); // Print the food char at the food coordinates
        }
        wrefresh(window); // Refresh the window
    }


    bool checkEatFood(int x, int y){ // Check if the snake head is on top of any food object
        for(int i = 0; i < this->foodVector.size(); i++){ // For each food object
            if(x == this->foodVector[i].x && y == this->foodVector[i].y){ // If the snake head is on top of the food object
                this->foodVector.erase(this->foodVector.begin() + i); // Remove food from vector
                this->foodVector.resize(this->foodVector.size() + 1); // Resize the vector to add one more food object
                this->foodVector[this->foodVector.size() - 1].x = rand() % LINES; // Set x coordinate to a random number between 0 and LINES
                this->foodVector[this->foodVector.size() - 1].y = rand() % COLS; // Set y coordinate to a random number between 0 and COLS
                return true; // Return true to indicate that the snake head ate the food
            }
        }
        return false; // Return false to indicate that the snake head did not eat the food
    }
};