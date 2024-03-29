#include "Paddle.h"

const int paddleSpeed  = 15;
const int SCREEN_WIDTH = 1000;

void renderPaddle(SDL_Renderer *renderer, Paddle &paddle) {
    SDL_Rect paddleRect = {paddle.x, paddle.y, paddle.width, paddle.height};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderFillRect(renderer, &paddleRect);
}

void paddleMove( Paddle &paddle, bool moveLeft, bool moveRight ) {
    if(moveLeft && paddle.x - paddleSpeed >= 0) {
        paddle.x -= paddleSpeed ;
    }

    if(moveRight && paddle.x + paddle.width + paddleSpeed <= SCREEN_WIDTH) {
        paddle.x += paddleSpeed ;
    }
}