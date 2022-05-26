#include <ncurses.h>
#include <unistd.h>
#include <vector>

struct foodStruct{
    int x;
    int y;
    char foodChar[2] = "*";
};

class foodClass{
public:
    std::vector<foodStruct> foodVector;
    foodClass(int n){
        foodVector.resize(n);
        for(int i = 0; i < foodVector.size(); i++){
            foodVector[i].x = rand() % LINES;
            foodVector[i].y = rand() % COLS;
        }
    }

    void drawFood(WINDOW* window){
        for(int i = 0; i < foodVector.size(); i++){
            mvwprintw(window, foodVector[i].x, foodVector[i].y, foodVector[i].foodChar);
        }
        wrefresh(window);
    }

    bool checkEatFood(int x, int y){
        for(int i = 0; i < foodVector.size(); i++){
            if(x == foodVector[i].x && y == foodVector[i].y){
                foodVector.erase(foodVector.begin() + i); // Remove food from vector
                // Add new food somewhere
                foodVector.resize(foodVector.size() + 1);
                foodVector[foodVector.size() - 1].x = rand() % LINES;
                foodVector[foodVector.size() - 1].y = rand() % COLS;
                return true;
            }
        }
        return false;
    }
};