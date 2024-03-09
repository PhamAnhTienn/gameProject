#ifndef BALL__H 
#define BALL__H

#include <SDL2/SDL.h>
#include "Paddle.h"
#include <iostream>
using namespace std;

class Ball {
private:
    int x, y, radius, Vx, Vy;
public:
    Ball(int x, int y, int radius) {
        this -> x = x;
        this -> y = y;
        this -> radius = radius;
        Vx = 5;
        Vy = 5;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getVx() { return Vx; }
    int getVy() { return Vy; }
    int getRadius() { return radius; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setVx(int newVx) {Vx = newVx; }
    void setVy(int newVy) {Vy = newVy; }
    void setRadius(int newRadius) { radius = newRadius; }
};

void renderBall(SDL_Renderer *renderer, Ball &Ball);
void ballMove(Ball &ball);
bool handleCollision(Paddle &paddle, Ball &ball);

#endif