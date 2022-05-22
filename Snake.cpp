#include "Snake.h"

using namespace std;

vector<vector<int>> Snake::getPoint(){
    return point;
}

int Snake::getSize(){
    return size_snake;
}

int Snake::getX(){
    return x;
}

int Snake::getY(){
    return y;
}

void Snake::turnUp(){
    stepX = 0;
    stepY = - step;
}

void Snake::turnDown(){
    stepX = 0;
    stepY = step;
}

void Snake::turnLeft(){
    stepX = - step;
    stepY = 0;
}

void Snake::turnRight(){
    stepX = step;
    stepY = 0;
}

void Snake::move(){
    x += stepX;
    y += stepY;
    vector<int> temp { x , y };
    point.push_back(temp);
}

bool Snake::checkDie(){
    if (x >= SCREEN_WIDTH || x < 0 || y >=SCREEN_HEIGHT || y < 0){
        return false;
    }
    return true;
}

bool Snake::eat(Food foodSnake){
    if (foodSnake.getX() == x && foodSnake.getY() == y){
        size_snake++;
        return true;
    }
    return false;
}

