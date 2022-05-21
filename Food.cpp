#include "Food.h"

using namespace std;

int Food::ramdomPointX(){
    return (rand() % (SCREEN_WIDTH/step))*step;
}

int Food::ramdomPointY(){
    return (rand() % (SCREEN_HEIGHT/step))*step;
}

void Food::newPoint(){
    x = ramdomPointX();
    y = ramdomPointY();
}

int Food::getX(){
    return x;
}

int Food::getY(){
    return y;
}
