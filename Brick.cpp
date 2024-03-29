#include "Brick.h"
#include <iostream>


void drawBricks(SDL_Renderer* renderer, vector<Brick>& bricks) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for ( Brick& brick : bricks ) {
        SDL_RenderFillRect(renderer, &brick.brick);
    }
}
