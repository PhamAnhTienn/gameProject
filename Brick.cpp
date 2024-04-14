#include "Brick.h"
#include "Ball.h"
#include <iostream>

void resetBricks(bool bricks[]) {
    for (int i = 0; i < ROW*COL; i++) {
        bricks[i] = true;
    }
}

void setBricks(int i, SDL_Rect &brick) {
    brick.w=(1000-(SPACING*COL))/COL;
    brick.h=22;
    brick.x=(((i%COL)+1)*SPACING)+((i%COL)*brick.w)-(SPACING/2);
    brick.y=brick.h*3+(((i%ROW)+1)*SPACING)+((i%ROW)*brick.h)-(SPACING/2);
}