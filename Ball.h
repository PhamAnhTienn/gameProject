#ifndef BALL__H 
#define BALL__H

#include <SDL2/SDL.h>
#include "Paddle.h"
#include <iostream>
using namespace std;

extern int vX; 
extern int vY;

const int radius = 5;

void setBallRect(int x, int y, int radius, SDL_Rect &ballRect);

void move(SDL_Rect &ballRect);

bool handleBallPaddleCollision(SDL_Rect &ballRect, Paddle& paddle);

#endif