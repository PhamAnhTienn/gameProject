#ifndef PADDLE__H 
#define PADDLE__H

#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

class Paddle {
public:
    int x, y, height, width;

    Paddle(int x, int y, int width, int height) {
        this -> x = x;
        this -> y = y;
        this -> width = width;
        this -> height = height;
    }
};

void paddleMove(Paddle &paddle, bool moveLeft, bool moveRight);

#endif