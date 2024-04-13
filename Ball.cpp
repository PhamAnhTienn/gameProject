#include "Ball.h"
#include <iostream>

int vX = 3; 
int vY = 3;

void move(SDL_Rect &ballRect) {
    ballRect.x = ballRect.x += vX;
    ballRect.y = ballRect.y += vY;

    if(ballRect.x - radius < 0 || ballRect.x + radius > 1000) {
        vX = -vX;
    }

    if(ballRect.y - radius < 0 || ballRect.y + radius > 700) {
        vY = -vY;
    }
}

bool handleBallPaddleCollision(SDL_Rect &ballRect, Paddle& paddle) {
    if(ballRect.x + radius > paddle.x && ballRect.x - radius < paddle.x + paddle.width &&
       ballRect.y + radius > paddle.y && ballRect.y - radius < paddle.y + paddle.height) {
        vY = -vY;
        return true;
    }
    return false;
}