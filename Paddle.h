#ifndef PADDLE__H 
#define PADDLE__H

#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

class Paddle {
private:
    int x, y, height, width;
public:
    Paddle(int x, int y, int width, int height) {
        this -> x = x;
        this -> y = y;
        this -> width = width;
        this -> height = height;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getWidth() { return width; }
    int getHeight() { return height; }

    void setX(int newX) { x = newX; }
    void setX(int newY) { x = newY; }
    void setX(int newWidth) { x = newWidth; }
    void setX(int newHeight) { x = newHeight; }

    void renderPaddle(SDL_Renderer *renderer, Paddle &paddle);
    void paddleMove(Paddle &paddle, const Uint8* currentKeyStates, bool moveLeft, bool moveRight);
};

#endif