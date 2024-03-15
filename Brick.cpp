#include "Brick.h"
#include <iostream>

void drawBricks(SDL_Renderer* renderer, vector<Brick>& bricks) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for ( Brick& brick : bricks ) {
        if (!brick.isDestroyed()) {
            SDL_Rect brickRect = brick.getRect();
            SDL_RenderFillRect(renderer, &brickRect);
        }
    }
}

void handleCollisions(vector<Brick>& bricks, SDL_Rect ballRect) {
    for (Brick& brick : bricks) {
        if (!brick.isDestroyed() && brick.checkCollision(ballRect)) {
            brick.destroy();
            // Xử lý các thay đổi khác, ví dụ: tăng điểm số, thay đổi hướng di chuyển của bóng, vv
        }
    }
}