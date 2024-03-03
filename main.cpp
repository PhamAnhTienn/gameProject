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

    Paddle paddle1(SCREEN_WIDTH / 2 - 25, SCREEN_HEIGHT - 10, 100, 10);
    Paddle paddle2(SCREEN_WIDTH / 2 - 25, 0, 100, 10);
    Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 3);

    initSDL(window, renderer, 1000, 700, WINDOW_TITLE);
    renderPaddle(renderer, paddle1);
    renderPaddle(renderer, paddle2);
    renderBall(renderer, ball);

    SDL_RenderPresent(renderer);
    quitSDL(window, renderer);
    return 0;
}