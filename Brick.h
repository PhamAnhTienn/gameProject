#ifndef BRICK__H 
#define BRICK__H

#define COL 7
#define ROW 5
#define SPACING 16

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "Ball.h"

using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;

class Brick {
public:

    SDL_Rect brick;
    bool bricks[ROW*COL];



    void setBricks(int i) {
        brick.x=(((i%COL)+1)*SPACING)+((i%COL)*brick.w)-(SPACING/2);
        brick.y=brick.h*3+(((i%ROW)+1)*SPACING)+((i%ROW)*brick.h)-(SPACING/2);
    }

    void resetBricks() {
        for(int i=0; i<COL*ROW; i++) {
            bricks[i]=1;
        }
    }

    void update(Ball &ball) {
        bool reset=1;
        for(int i=0; i<COL*ROW; i++) {
            setBricks(i);
            if(SDL_HasIntersection( &ball.ballRect, &brick) && bricks[i]) {
                bricks[i]=0;
                if(ball.x >= brick.x) { ball.Vx = -ball.Vx ; ball.x-=20;}
                if(ball.x <= brick.x) { ball.Vx = -ball.Vx ; ball.x+=20;}
                if(ball.y <= brick.y) { ball.Vy = -ball.Vy ; ball.y-=20;}
                if(ball.y >= brick.y) { ball.Vy = -ball.Vy ; ball.y+=20;}
            }
            if(bricks[i]) reset=0;
        }
        if(reset) resetBricks();
    }

};

void drawBricks(SDL_Renderer* renderer);

#endif