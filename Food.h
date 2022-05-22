#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SDL_utilities.h"

using namespace std;

class Food{
private:
    int x;
    int y;
public:
    food(){
        x = ramdomPointX();
        y = ramdomPointY();
    }
    int ramdomPointX();
    int ramdomPointY();
    void newPoint();
    int getX();
    int getY();
};

#endif // FOOD_H_INCLUDED

