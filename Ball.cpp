#include "Ball.h"
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

void renderBall(SDL_Renderer *renderer, Ball &Ball){
    const int diameter = (Ball.getRadius() * 2);
    int x_rect = Ball.getX() - Ball.getRadius();
    int y_rect = Ball.getY() - Ball.getRadius();

    SDL_Rect ballRect = {x_rect, y_rect, diameter, diameter};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ballRect);
}

void ballMove(Ball &ball) {
    ball.setX(ball.getX() + ball.getVx());
    ball.setY(ball.getY() + ball.getVy());

    if(ball.getX() - ball.getRadius() < 0 || ball.getX() + ball.getRadius() > SCREEN_WIDTH) {
        ball.setVx( -ball.getVx() );
    }

    if(ball.getY() - ball.getRadius() < 0 || ball.getY() + ball.getRadius() > SCREEN_HEIGHT) {
        ball.setVy( -ball.getVy() );
    }
}


bool handleCollision(Paddle &paddle, Ball &ball) {
    if( ball.getX() + ball.getRadius() > paddle.getX() && ball.getX() - ball.getRadius() < paddle.getX() + paddle.getWidth() 
   && ( ball.getY() + ball.getRadius() > paddle.getY() && ball.getY() - ball.getRadius() < paddle.getY() + paddle.getHeight() ) ) {
            ball.setVy( -ball.getVy() );
            return true;
    }
    return false;
}