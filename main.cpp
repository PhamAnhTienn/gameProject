#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "SDL_utils.h"
#include "image.h"
#include "Sound.h"
#include "Text.h"
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

    Paddle paddle1(SCREEN_WIDTH / 2 - 88, SCREEN_HEIGHT - 30, 200, 15);
    setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5);

    initSDL(window, renderer, 1000, 700, WINDOW_TITLE);

    SDL_Texture * menuImage = loadTexture("assets/menuImage.png", renderer);
    SDL_Texture * backgroundImage = loadTexture("assets/backgroundImage.png", renderer);
    SDL_Texture * gameOverImage = loadTexture("assets/gameOverImage.png", renderer);
    SDL_Texture * cursorImage = loadTexture("assets/cursor_hand.png", renderer);
    SDL_Texture * paddleImage = loadTexture("assets/paddleRed.png", renderer);
    SDL_Texture * ballImage = loadTexture("assets/ballImage.png", renderer);

    SDL_Texture * brickRed = loadTexture("assets/element_red_rectangle.png", renderer);
    SDL_Texture * brickYellow = loadTexture("assets/element_yellow_rectangle.png", renderer);
    SDL_Texture * brickGreen = loadTexture("assets/element_green_rectangle.png", renderer);
    SDL_Texture * brickBlue = loadTexture("assets/element_blue_rectangle.png", renderer);
    SDL_Texture * brickPurple = loadTexture("assets/element_purple_rectangle.png", renderer);
    SDL_Texture * brickGrey = loadTexture("assets/element_grey_rectangle.png", renderer);

    Mix_Music* menuSound = loadMusic("assets/backgroundMusic.mp3");
    Mix_Chunk* ballCollisionPaddle = loadSound("assets/collisionsound.wav");
    Mix_Chunk* brickCollisionBall = loadSound("assets/brickCollision.mp3");

    TTF_Font* liveCountFont = loadFont("assets/GayoLand-Rounded.ttf", 36);
    SDL_Color color = {255, 0, 255, 0}; 

    State gameState = MENU;
    bool waitingForClick = false;

    int liveCount = 3;
    SDL_Texture* liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);

    while (gameState == MENU) {
        SDL_Event menuEvent;
        renderTexture(menuImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
        SDL_RenderPresent(renderer);
		SDL_RenderClear(renderer);
        playMusic(menuSound);
        while ( SDL_PollEvent(&menuEvent) != 0 ) {
            if (menuEvent.type == SDL_QUIT) gameState = QUIT;
            if (menuEvent.type == SDL_MOUSEBUTTONDOWN) {
                int posX = menuEvent.button.x;
				int posY = menuEvent.button.y;
                SDL_GetMouseState(&posX, &posY);
                cerr << posX << ", " << posY << endl;
				if (posX >= 335 && posX <= 656 && posY >= 305 && posY <= 374) {
                    gameState = GAME;
                    stopBackgroundMusic();

                    while (gameState == GAME) { 
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
                            } else if (e.type == SDL_MOUSEBUTTONDOWN && !waitingForClick) {
                                int posX = e.button.x;
                                int posY = e.button.y;
                                SDL_GetMouseState(&posX, &posY);
                                cerr << posX << ", " << posY << endl;
                                waitingForClick = true;
                            }
                        }

                        if (waitingForClick) move(ballRect);

                        if ( ballRect.y + ballRect.h >= SCREEN_HEIGHT ) {
                            liveCount--;
                            if (liveCount == 2) liveCountText =  renderText("LIVES: 2", liveCountFont, color, renderer);
                            else if (liveCount == 1) liveCountText =  renderText("LIVES: 1", liveCountFont, color, renderer);
                            else if (liveCount == 0) gameState = GAME_OVER;
                            setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5);
                            renderTextureText(liveCountText, 500, 500, renderer);
                            waitingForClick = false;
                        }
                        
                        if (handleBallPaddleCollision(ballRect, paddle1)) {
                            playChunk(ballCollisionPaddle);
                        }
                        
                        for(int i=0; i<COL*ROW; i++) {
                            setBricks(i);
                            if(SDL_HasIntersection( &ballRect, &brick ) && bricks[i]) {
                                bricks[i] = false;
                                playChunk(brickCollisionBall);
                                if(ballRect.x >= brick.x) { vX = -vX ; ballRect.x-=10;}
                                if(ballRect.x <= brick.x) { vX = -vX ; ballRect.x+=10;}
                                if(ballRect.y <= brick.y) { vY = -vY ; ballRect.y-=10;}
                                if(ballRect.y >= brick.y) { vY = -vY ; ballRect.y+=10;}
                            }
                        }
 
                        SDL_RenderClear(renderer);
                        renderTexture(backgroundImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                        renderTexture(paddleImage, paddle1.x, paddle1.y, paddle1.width, paddle1.height, renderer);
                        renderTexture(ballImage, ballRect.x - radius, ballRect.y - radius, radius*2, radius*2, renderer);
                        renderTextureText(liveCountText, 416, 27, renderer);

                        for (int i = 0; i < ROW*COL; i++) {
                            if (bricks[i]) {
                                setBricks(i);
                                if (i % 6 == 0) renderTexture(brickRed, brick.x, brick.y, brick.w, brick.h, renderer); 
                                else if (i % 6 == 1) renderTexture(brickYellow, brick.x, brick.y, brick.w, brick.h, renderer); 
                                else if (i % 6 == 2) renderTexture(brickGreen, brick.x, brick.y, brick.w, brick.h, renderer); 
                                else if (i % 6 == 3) renderTexture(brickBlue, brick.x, brick.y, brick.w, brick.h, renderer); 
                                else if (i % 6 == 4) renderTexture(brickGrey, brick.x, brick.y, brick.w, brick.h, renderer); 
                                else if (i % 6 == 5) renderTexture(brickPurple, brick.x, brick.y, brick.w, brick.h, renderer); 
                            }
                        }

                        SDL_RenderPresent(renderer);
                        SDL_Delay(16);

                        //gameOver
                        while (gameState == GAME_OVER) {
                            SDL_Event finalEvent;
                            while ( SDL_PollEvent(&finalEvent) != 0 ) {
                                if (finalEvent.type == SDL_QUIT) {
                                    gameState = QUIT;
                                } else if (finalEvent.type == SDL_MOUSEBUTTONDOWN) {
                                    int posX = finalEvent.button.x;
                                    int posY = finalEvent.button.y;
                                    SDL_GetMouseState(&posX, &posY);
                                    cerr << posX << ", " << posY << endl;

                                    if ( posX >= 353 && posX <= 646 && posY >= 499 && posY <= 552 ) {
                                        liveCount = 3;
                                        gameState = GAME;
                                    } else if ( posX >= 353 && posX <= 646 && posY >= 594 && posY <= 648 ) {
                                        gameState = QUIT;
                                    }
                                }
                            }

                            renderTexture(gameOverImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                            SDL_RenderPresent(renderer);
                        }
                    }
                }

                if (posX >= 335 && posX <= 656 && posY >= 418 && posY <= 487) {
                    
                }

                if (posX >= 335 && posX <= 656 && posY >= 530 && posY <= 604) {
                    gameState = QUIT;
                }
            }
        }
    }

    quitSDL(window, renderer);
    return 0;
}