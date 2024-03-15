#ifndef BRICK__H 
#define BRICK__H

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
using namespace std;

const int NUM_BRICKS = 50;

class Brick {
private:
    const int brickWidth = 80;
    const int brickHeight = 20;
    bool destroyed;
    SDL_Rect brickRect;
    vector<Brick> bricks;
public:
    Brick() {}

    Brick(int x, int y) {
        destroyed = false;
        brickRect.x = x;
        brickRect.y = y;
        brickRect.w = brickWidth;
        brickRect.h = brickHeight;
    }

    int getBrickWidth() {return brickWidth;}
    int getBrickHeight() {return brickHeight;}
    SDL_Rect getRect() { return brickRect; }
    bool isDestroyed() { return destroyed; }
    void destroy() { destroyed = true; }

    vector<Brick> createBricks() {
        const int startX = 50; 
        const int startY = 50; 
        const int gapX = 5; 
        const int gapY = 5; // Điều chỉnh khoảng cách giữa các hàng viên gạch
        int currentX = startX;
        int currentY = startY;

        // Tính toán số lượng hàng cần tạo ra
        int numRows = NUM_BRICKS / 10; // Mỗi hàng có 10 viên gạch

        for (int i = 0; i < NUM_BRICKS; ++i) {
            bricks.emplace_back(currentX, currentY);
            currentX += brickWidth + gapX;
            if (currentX + brickWidth > 1000) {
                currentX = startX;
                currentY += brickHeight + gapY;
            }
        }

        return bricks;
    }

    bool checkCollision(SDL_Rect ballRect) {
        return SDL_HasIntersection(&brickRect, &ballRect);
    }
};

void drawBricks(SDL_Renderer* renderer, vector<Brick>& bricks);
void handleCollisions(vector<Brick>& bricks, SDL_Rect ballRect);

#endif