#include "Brick.h"
#include "Ball.h"
#include <iostream>

void resetBricks(bool bricks[]) {
    for (int i = 0; i < ROW*COL; i++) {
        bricks[i] = true;
    }
}

