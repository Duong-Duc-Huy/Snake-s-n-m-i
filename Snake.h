#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include <vector>
#include "Food.h"

using namespace std;

class Snake{
private:
    int x;
    int y;
    int size_snake;
    int stepX,stepY;
    vector<vector<int>> point;
public:
    Snake(){
        x = -25;
        y = 100;
        size_snake = 3;
        stepX = step;
        stepY = 0;
        point = { {0,100} };
    }
    vector<vector<int>> getPoint();
    int getSize();
    int getX();
    int getY();
    void turnUp();
    void turnDown();
    void turnLeft();
    void turnRight();
    void move();
    bool checkDie();
    bool eat(Food foodSnake);
};

#endif // SNAKE_H_INCLUDED

