#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_utils.h"
#include "image.h"
#include "Sound.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "BRICK BREAKER";

enum State {
    MENU,
    GAME,
    GAME_OVER,
    QUIT
};

SDL_Rect brick;
SDL_Rect ballRect;

void setBallRect(int x, int y, int radius) {
    const int diameter = (radius * 2);

    int x_rect = x - radius;
    int y_rect = y - radius;

    ballRect = {x_rect, y_rect, diameter, diameter};
}

void setBricks(int i) {
    brick.w=(1000-(SPACING*COL))/COL;
    brick.h=22;
    brick.x=(((i%COL)+1)*SPACING)+((i%COL)*brick.w)-(SPACING/2);
    brick.y=brick.h*3+(((i%ROW)+1)*SPACING)+((i%ROW)*brick.h)-(SPACING/2);
}

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    bool bricks[ROW*COL];
    resetBricks(bricks);

    Paddle paddle1(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT - 10, 100, 5);
    setBallRect(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5);

    initSDL(window, renderer, 1000, 700, WINDOW_TITLE);

    SDL_Texture * backgroundImage = loadTexture("assets/backgroundImage.png", renderer);
    SDL_Texture * paddleImage = loadTexture("assets/glasspaddle2.png", renderer);
    SDL_Texture * ballImage = loadTexture("assets/ballImage.png", renderer);

    Mix_Chunk* ballCollisionPaddle = loadSound("assets/collisionsound.wav");

    State gameState = MENU;

    while (gameState == MENU) {
        SDL_Event e;
        while ( SDL_PollEvent(&e) != 0 ) {
            if (e.type == SDL_QUIT) {
                gameState = QUIT;
            } else if () { // xử lí chuột

            }
        }
    }

    while (gameState == GAME)
    {
        SDL_Event e;
        while ( SDL_PollEvent(&e) != 0 )
        {
            if (e.type == SDL_QUIT)
            {
                gameState = QUIT;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

                bool moveLeft = currentKeyStates[SDL_SCANCODE_LEFT];
                bool moveRight = currentKeyStates[SDL_SCANCODE_RIGHT];

                paddleMove(paddle1, moveLeft, moveRight);
            }
        }

        move(ballRect);
        if (handleBallPaddleCollision(ballRect, paddle1)) {
            playChunk(ballCollisionPaddle);
        }
        
        for(int i=0; i<COL*ROW; i++) {
            setBricks(i);
            if(SDL_HasIntersection( &ballRect, &brick ) && bricks[i]) {
                bricks[i] = false;
                if(ballRect.x >= brick.x) { vX = -vX ; ballRect.x-=20;}
                if(ballRect.x <= brick.x) { vX = -vX ; ballRect.x+=20;}
                if(ballRect.y <= brick.y) { vY = -vY ; ballRect.y-=20;}
                if(ballRect.y >= brick.y) { vY = -vY ; ballRect.y+=20;}
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);

        renderTexture(backgroundImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
        renderTexture(paddleImage, paddle1.x, paddle1.y, paddle1.width, paddle1.height, renderer);
        renderTexture(ballImage, ballRect.x - radius, ballRect.y - radius, radius*2, radius*2, renderer);

        for (int i = 0; i < ROW*COL; i++) {
            if (i % 4 == 0) SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255); // Màu xanh da trời
            else if (i % 4 == 1) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Màu đỏ
            else if (i % 4 == 2) SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); // Màu vàng
            else SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Màu xanh lá 

            if (bricks[i]) {
                setBricks(i);
                SDL_RenderFillRect(renderer, &brick);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    quitSDL(window, renderer);
    return 0;
}