#ifndef GAME__H 
#define GAME__H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#define COL 7
#define ROW 5
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 700;
const string WINDOW_TITLE = "BRICK BREAKER";



enum State {
    MENU,
    OPTIONS,
    EASY,
    MEDIUM,
    HARD,
    GAME,
    WIN,
    GAME_OVER,
    QUIT
};

class Game {
public: 
    void playAgain(bool medium, bool hard);
    void winGame(bool medium, bool hard);
    void initGame();
    void easyGame();
    void mediumGame();
    void hardGame();
    void optionsGame();
    void runningGame();

    SDL_Rect brick;
    SDL_Rect ballRect;
    SDL_Renderer* renderer;
    SDL_Window* window;

    bool bricks[ROW*COL];
    int brickHits[ROW * COL] = {0};

    bool waitingForClick = false;
    bool medium = false;
    bool easy = false;
    bool hard = false;

    State gameState = MENU;

    int liveCount = 3;
    int score = 0;
    int highScore = 0;

    SDL_Texture * menuImage;
    SDL_Texture * optionImage;
    SDL_Texture * easyImage;
    SDL_Texture * mediumImage;
    SDL_Texture * hardImage;
    SDL_Texture * backgroundImage;
    SDL_Texture * gameOverImage;
    SDL_Texture * winImage;
    SDL_Texture * cursorImage;
    SDL_Texture * paddleImage;
    SDL_Texture * ballImage;

    SDL_Texture * brickRed;
    SDL_Texture * brickYellow;
    SDL_Texture * brickGreen;
    SDL_Texture * brickBlue;
    SDL_Texture * brickPurple;
    SDL_Texture * brickGrey;

    Mix_Music* menuSound;
    Mix_Chunk* ballCollisionPaddle;
    Mix_Chunk* brickCollisionBall;

    TTF_Font* liveCountFont;
    TTF_Font* highScoreFont;
    TTF_Font* scoreFont;
    SDL_Color color; 

    SDL_Texture* liveCountText;
    SDL_Texture* scoreText;
    SDL_Texture* highScoreText;
};

#endif