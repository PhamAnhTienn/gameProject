#include "Paddle.h"

int paddleSpeed  = 15;
const int SCREEN_WIDTH = 1000;

void paddleMove( Paddle &paddle, bool moveLeft, bool moveRight ) {
    if(moveLeft && paddle.x - paddleSpeed >= 0) {
        paddle.x -= paddleSpeed ;
    }

    if(moveRight && paddle.x + paddle.width + paddleSpeed <= SCREEN_WIDTH) {
        paddle.x += paddleSpeed ;
    }
}