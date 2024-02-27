#include "Paddle.h"

const int paddleSpeed  = 15;
const int SCREEN_WIDTH = 1000;

void renderPaddle(SDL_Renderer *renderer, Paddle &paddle) {
    SDL_Rect paddleRect = {paddle.getX(), paddle.getY(), paddle.getWidth(), paddle.getHeight()};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
    SDL_RenderFillRect(renderer, &paddleRect);
}

void paddleMove(Paddle &paddle, const Uint8* currentKeyStates, bool moveLeft, bool moveRight) {
    if(moveLeft && paddle.getX() - paddleSpeed >= 0) {
        paddle.setX(paddle.getX() - paddleSpeed);
    }

    if(moveRight && paddle.getX() + paddle.getWidth() + paddleSpeed <= SCREEN_WIDTH) {
        paddle.setX(paddle.getX() + paddleSpeed);
    }
}