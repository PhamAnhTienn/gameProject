#include "Ball.h"
#include <iostream>

int vX = 5; 
int vY = 5;

void setBallRect(int x, int y, int radius, SDL_Rect &ballRect) {
    const int diameter = (radius * 2);

    int x_rect = x - radius;
    int y_rect = y - radius;

    ballRect = {x_rect, y_rect, diameter, diameter};
}

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