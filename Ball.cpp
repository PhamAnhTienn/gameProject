#include "Ball.h"
#include <iostream>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

void renderBall(SDL_Renderer *renderer, Ball &Ball){
    SDL_Rect ballRect = {Ball.getX(), Ball.getY(), Ball.getEdge(), Ball.getEdge()};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &ballRect);
}

void ballMove(Ball &ball) {
    ball.setX(ball.getX() + ball.getVx());
    ball.setY(ball.getY() + ball.getVy());

    if(ball.getX() < 0 || ball.getX() + ball.getEdge() > SCREEN_WIDTH) {
        ball.setVx( -ball.getVx() );
    }

    if(ball.getY() < 0 || ball.getY() + ball.getEdge() > SCREEN_HEIGHT) {
        ball.setVy( -ball.getVy() );
    }
}


bool handleCollision(Paddle &paddle, Ball &ball) {
    if( ball.getX() + ball.getEdge() > paddle.getX() && ball.getX() < paddle.getX() + paddle.getWidth() 
     && ( ball.getY() + ball.getEdge() > paddle.getY() || ball.getY() < paddle.getX() + paddle.getHeight() ) ) {
            ball.setVy( -ball.getVy() );
            return true;
    }
    return false;
}