#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_utils.h"
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
    
    initSDL(window, renderer, 1000, 700, WINDOW_TITLE);
    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}