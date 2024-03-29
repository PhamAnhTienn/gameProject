#include "Ball.h"
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

void renderBall(SDL_Renderer *renderer, Ball &Ball){
    const int diameter = (Ball.radius * 2);
    int x_rect = Ball.x - Ball.radius;
    int y_rect = Ball.y - Ball.radius;

    SDL_Rect ballRect = {x_rect, y_rect, diameter, diameter};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ballRect);
}

void ballMove(Ball &ball) {
    ball.x += ball.Vx;
    ball.y += ball.Vy;

    if(ball.x - ball.radius < 0 || ball.x + ball.radius > SCREEN_WIDTH) {
        ball.Vx = -ball.Vx ;
    }

    if(ball.y - ball.radius < 0 || ball.y + ball.radius > SCREEN_HEIGHT) {
        ball.Vy = -ball.Vy ;
    }
}


bool handleCollision(Paddle &paddle, Ball &ball) {
    if( ball.x + ball.radius > paddle.x && ball.x - ball.radius < paddle.x + paddle.width 
   && ( ball.y + ball.radius > paddle.y && ball.y - ball.radius < paddle.y + paddle.height ) ) {
            ball.Vy = -ball.Vy ;
            return true;
    }
    return false;
}
