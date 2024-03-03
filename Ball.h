#ifndef BALL__H 
#define BALL__H

#include <SDL2/SDL.h>
#include "Paddle.h"
#include <iostream>
using namespace std;

class Ball {
private:
    int x, y, edge, Vx, Vy;
public:
    Ball(int x, int y, int edge) {
        this -> x = x;
        this -> y = y;
        this -> edge = edge;
        Vx = 1;
        Vy = 1;
    }

    int getX() { return x; }
    int getY() { return y; }
    int getVx() { return Vx; }
    int getVy() { return Vy; }
    int getEdge() { return edge; }

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    void setVx(int newVx) {Vx = newVx; }
    void setVy(int newVy) {Vy = newVy; }
    void setEdge(int newEdge) { edge = newEdge; }
};

void renderBall(SDL_Renderer *renderer, Ball &Ball);
void ballMove(Ball &ball);
bool handleCollision(Paddle &paddle, Ball &ball);

#endif