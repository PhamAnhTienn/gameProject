#ifndef BALL__H 
#define BALL__H

#include <SDL2/SDL.h>
#include "Paddle.h"
#include "Brick.h"
#include <iostream>
using namespace std;

class Ball {
public:
    int x, y, radius, Vx, Vy;
    SDL_Rect ballRect;

    Ball(int x, int y, int radius) {
        this -> x = x;
        this -> y = y;
        this -> radius = radius;
        Vx = 5;
        Vy = 5;
    }
};

void renderBall(SDL_Renderer *renderer, SDL_Rect ballRect, Ball &Ball);
void ballMove(Ball &ball);
bool handleCollision(Paddle &paddle, Ball &ball);

#endif