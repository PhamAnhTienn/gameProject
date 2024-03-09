#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_utils.h"
#include "Paddle.h"
#include "Ball.h"
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "Pong Game";

enum State {
    MENU,
    GAME,
    GAME_OVER,
    QUIT
};

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;

    Paddle paddle1(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT - 10, 100, 5);
    Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5);

    initSDL(window, renderer, 1000, 700, WINDOW_TITLE);

    bool quit = false;
    SDL_Event e;

    while (!quit)
    {
        while ( SDL_PollEvent(&e) != 0 )
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

                bool moveLeft = currentKeyStates[SDL_SCANCODE_LEFT];
                bool moveRight = currentKeyStates[SDL_SCANCODE_RIGHT];

                paddleMove(paddle1, moveLeft, moveRight);
            }
        }

        ballMove(ball);
        handleCollision(paddle1, ball);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); 
        SDL_RenderClear(renderer);

        renderPaddle(renderer, paddle1);
        renderBall(renderer, ball);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    quitSDL(window, renderer);
    return 0;
}