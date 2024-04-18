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

void resetBricks(bool bricks[]);

void resetBrickHits(int brickHits[]);

void setBricks(int i, SDL_Rect &brick);

bool isWinning(bool bricks[]);

#endif