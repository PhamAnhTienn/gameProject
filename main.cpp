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
#include "HighScore.h"
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

int main(int argc, char* argv[]) {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Rect brick;
    SDL_Rect ballRect;

    bool bricks[ROW*COL];
    int brickHits[ROW * COL] = {0};
    resetBricks(bricks);

    Paddle paddle1(SCREEN_WIDTH / 2 - 88, SCREEN_HEIGHT - 30, 200, 15);
    setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5, ballRect);

    initSDL(window, renderer, 1000, 700, WINDOW_TITLE);

    SDL_Texture * menuImage = loadTexture("assets/menuImage.png", renderer);
    SDL_Texture * optionImage = loadTexture("assets/optionImage.png", renderer);
    SDL_Texture * easyImage = loadTexture("assets/easyImage.png", renderer);
    SDL_Texture * mediumImage = loadTexture("assets/mediumImage.png", renderer);
    SDL_Texture * hardImage = loadTexture("assets/hardImage.png", renderer);
    SDL_Texture * backgroundImage = loadTexture("assets/backgroundImage.png", renderer);
    SDL_Texture * gameOverImage = loadTexture("assets/gameOverImage.png", renderer);
    SDL_Texture * winImage = loadTexture("assets/winImage.png", renderer);
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
    TTF_Font* highScoreFont = loadFont("assets/GayoLand-Rounded.ttf", 36);
    TTF_Font* scoreFont = loadFont("assets/GayoLand-Rounded.ttf", 36);
    SDL_Color color = {255, 0, 255, 0}; 

    State gameState = MENU;
    bool waitingForClick = false;
    bool medium = false;
    bool easy = false;
    bool hard = false;

    int liveCount = 3;
    SDL_Texture* liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
    
    int score = 0;
    int highScore = 0;
    SDL_Texture* scoreText =  renderText( "SCORE: " + to_string(score) , liveCountFont, color, renderer);
    SDL_Texture* highScoreText = renderText( "HIGH SCORE: " + to_string(highScore) , liveCountFont, color, renderer);

    while (gameState == MENU) {
        SDL_Event menuEvent;
        SDL_RenderClear(renderer);
        renderTexture(menuImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
        SDL_RenderPresent(renderer);
        playMusic(menuSound);
        while ( SDL_PollEvent(&menuEvent) != 0 ) {
            if (menuEvent.type == SDL_QUIT) gameState = QUIT;
            if (menuEvent.type == SDL_MOUSEBUTTONDOWN) {
                int posX = menuEvent.button.x;
				int posY = menuEvent.button.y;
                SDL_GetMouseState(&posX, &posY);
                cerr << posX << ", " << posY << endl;

                //option
                if (posX >= 335 && posX <= 656 && posY >= 418 && posY <= 487) {
                    gameState = OPTIONS;
                    while (gameState == OPTIONS) {
                        SDL_Event optionEvent;
                        while ( SDL_PollEvent(&optionEvent) != 0 ) {
                            if (optionEvent.type == SDL_QUIT) gameState = QUIT;
                            if (optionEvent.type == SDL_MOUSEBUTTONDOWN) {
                                int posX = optionEvent.button.x;
                                int posY = optionEvent.button.y;
                                SDL_GetMouseState(&posX, &posY);
                                cerr << posX << ", " << posY << endl; 

                                //easy
                                if (posX >= 335 && posX <= 656 && posY >= 305 && posY <= 374) {
                                    gameState = EASY;
                                    easy = true;
                                    medium = false;
                                    hard = false;
                                    while (gameState == EASY) {
                                        SDL_Event easyEvent;
                                        while ( SDL_PollEvent(&easyEvent) != 0 ) {
                                            if (easyEvent.type == SDL_QUIT) gameState = QUIT;
                                            if (easyEvent.type == SDL_MOUSEBUTTONDOWN) {
                                                int posX = easyEvent.button.x;
                                                int posY = easyEvent.button.y;
                                                if (posX >= 335 && posX <= 656 && posY >= 530 && posY <= 604) gameState = MENU;
                                            }
                                        }

                                        SDL_RenderClear(renderer);
                                        renderTexture(easyImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                        SDL_RenderPresent(renderer);
                                    }
                                }

                                //medium
                                if (posX >= 335 && posX <= 656 && posY >= 418 && posY <= 487) {
                                    gameState = MEDIUM;
                                    easy = false;
                                    medium = true;
                                    hard = false;
                                    while (gameState == MEDIUM) {
                                        SDL_Event mediumEvent;
                                        while ( SDL_PollEvent(&mediumEvent) != 0 ) {
                                            if (mediumEvent.type == SDL_QUIT) gameState = QUIT;
                                            if (mediumEvent.type == SDL_MOUSEBUTTONDOWN) {
                                                int posX = mediumEvent.button.x;
                                                int posY = mediumEvent.button.y;
                                                if (posX >= 335 && posX <= 656 && posY >= 530 && posY <= 604) gameState = MENU;
                                            }
                                        }

                                        SDL_RenderClear(renderer);
                                        renderTexture(mediumImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                        SDL_RenderPresent(renderer);
                                    }
                                }

                                //hard
                                if (posX >= 335 && posX <= 656 && posY >= 530 && posY <= 604) {
                                    gameState = HARD;
                                    easy = false;
                                    medium = false;
                                    hard = true;
                                    while (gameState == HARD) {
                                        SDL_Event hardEvent;
                                        while ( SDL_PollEvent(&hardEvent) != 0 ) {
                                            if (hardEvent.type == SDL_QUIT) gameState = QUIT;
                                            if (hardEvent.type == SDL_MOUSEBUTTONDOWN) {
                                                int posX = hardEvent.button.x;
                                                int posY = hardEvent.button.y;
                                                if (posX >= 335 && posX <= 656 && posY >= 530 && posY <= 604) gameState = MENU;
                                            }
                                        }

                                        SDL_RenderClear(renderer);
                                        renderTexture(hardImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                        SDL_RenderPresent(renderer);
                                    }
                                }
                            }
                        }

                        SDL_RenderClear(renderer);
                        renderTexture(optionImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                        SDL_RenderPresent(renderer);
                    }
                }

                //quit game
                if (posX >= 335 && posX <= 656 && posY >= 530 && posY <= 604) {
                    gameState = QUIT;
                }

                //play game
				if (posX >= 335 && posX <= 656 && posY >= 305 && posY <= 374) {
                    gameState = GAME;
                    stopBackgroundMusic();

                    if ( !easy && !medium && !hard ) easy = true;
                    //easy
                    if (easy) {
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
                            
                            if ( isWinning(bricks) ) {
                                gameState = WIN;

                                while (gameState == WIN) {
                                    SDL_Event winEvent;
                                    while ( SDL_PollEvent(&winEvent) != 0 ) {
                                        if (winEvent.type == SDL_QUIT) {
                                            gameState = QUIT;
                                        } else if (winEvent.type == SDL_MOUSEBUTTONDOWN) {
                                            int posX = winEvent.button.x;
                                            int posY = winEvent.button.y;
                                            SDL_GetMouseState(&posX, &posY);
                                            cerr << posX << ", " << posY << endl;

                                            if ( posX >= 128 && posX <= 458 && posY >= 563 && posY <= 636 ) {
                                                liveCount = 3;
                                                liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
                                                resetBricks(bricks);
                                                setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5, ballRect);
                                                gameState = GAME;
                                                highScore = max(highScore, score);
                                                score = 0;
                                                scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
                                                saveHighScore("assets/highScore.txt", highScore);
                                                loadHighScore("assets/highScore.txt", highScore);
                                                highScoreText = renderText( "HIGH SCORE: " + to_string(highScore) , liveCountFont, color, renderer);
                                            } else if ( posX >= 538 && posX <= 869 && posY >= 564 && posY <= 635 ) {
                                                gameState = QUIT;
                                            }
                                        }
                                    }

                                    SDL_RenderClear(renderer);
                                    renderTexture(winImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                    SDL_RenderPresent(renderer);
                                }
                            }

                            if ( ballRect.y + ballRect.h >= SCREEN_HEIGHT ) {
                                liveCount--;
                                if (liveCount == 2) liveCountText =  renderText("LIVES: 2", liveCountFont, color, renderer);
                                else if (liveCount == 1) liveCountText =  renderText("LIVES: 1", liveCountFont, color, renderer);
                                else if (liveCount == 0) gameState = GAME_OVER;
                                setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5, ballRect);
                                renderTextureText(liveCountText, 500, 500, renderer);
                                waitingForClick = false;
                            }
                            
                            if (handleBallPaddleCollision(ballRect, paddle1)) {
                                playChunk(ballCollisionPaddle);
                            }
                            
                            for(int i=0; i<COL*ROW; i++) {
                                setBricks(i, brick);
                                if(SDL_HasIntersection( &ballRect, &brick ) && bricks[i]) {
                                    score += 20;
                                    scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
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
                            renderTextureText(scoreText, 35, 27, renderer);
                            renderTextureText(liveCountText, 351, 27, renderer);
                            renderTextureText(highScoreText, 594, 27, renderer);
                            

                            for (int i = 0; i < ROW*COL; i++) {
                                if (bricks[i]) {
                                    setBricks(i, brick);
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
                                            liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
                                            resetBricks(bricks);
                                            gameState = GAME;
                                            highScore = max(highScore, score);
                                            score = 0;
                                            scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
                                            saveHighScore("assets/highScore.txt", highScore);
                                            loadHighScore("assets/highScore.txt", highScore);
                                            highScoreText = renderText( "HIGH SCORE: " + to_string(highScore) , liveCountFont, color, renderer);
                                        } else if ( posX >= 353 && posX <= 646 && posY >= 594 && posY <= 648 ) {
                                            gameState = QUIT;
                                        }
                                    }
                                }

                                SDL_RenderClear(renderer);
                                renderTexture(gameOverImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                SDL_RenderPresent(renderer);
                            }
                        }
                    }
                    //medium
                    if ( medium ) {
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

                            if ( isWinning(bricks) ) {
                                gameState = WIN;

                                while (gameState == WIN) {
                                    SDL_Event winEvent;
                                    while ( SDL_PollEvent(&winEvent) != 0 ) {
                                        if (winEvent.type == SDL_QUIT) {
                                            gameState = QUIT;
                                        } else if (winEvent.type == SDL_MOUSEBUTTONDOWN) {
                                            int posX = winEvent.button.x;
                                            int posY = winEvent.button.y;
                                            SDL_GetMouseState(&posX, &posY);
                                            cerr << posX << ", " << posY << endl;

                                            if ( posX >= 128 && posX <= 458 && posY >= 563 && posY <= 636 ) {
                                                liveCount = 3;
                                                liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
                                                resetBricks(bricks);
                                                resetBrickHits(brickHits);
                                                setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5, ballRect);
                                                gameState = GAME;
                                                highScore = max(highScore, score);
                                                score = 0;
                                                scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
                                                saveHighScore("assets/highScore.txt", highScore);
                                                loadHighScore("assets/highScore.txt", highScore);
                                                highScoreText = renderText( "HIGH SCORE: " + to_string(highScore) , liveCountFont, color, renderer);
                                            } else if ( posX >= 538 && posX <= 869 && posY >= 564 && posY <= 635 ) {
                                                gameState = QUIT;
                                            }
                                        }
                                    }

                                    SDL_RenderClear(renderer);
                                    renderTexture(winImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                    SDL_RenderPresent(renderer);
                                }
                            }

                            if ( ballRect.y + ballRect.h >= SCREEN_HEIGHT ) {
                                liveCount--;
                                if (liveCount == 2) liveCountText =  renderText("LIVES: 2", liveCountFont, color, renderer);
                                else if (liveCount == 1) liveCountText =  renderText("LIVES: 1", liveCountFont, color, renderer);
                                else if (liveCount == 0) gameState = GAME_OVER;
                                setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5, ballRect);
                                renderTextureText(liveCountText, 500, 500, renderer);
                                waitingForClick = false;
                            }
                            
                            if (handleBallPaddleCollision(ballRect, paddle1)) {
                                playChunk(ballCollisionPaddle);
                            }
                            
                            for(int i=0; i<COL*ROW; i++) {
                                setBricks(i, brick);
                                if(SDL_HasIntersection( &ballRect, &brick ) && bricks[i]) {
                                    brickHits[i]++;
                                    playChunk(brickCollisionBall);
                                    if (brickHits[i] >= 2) {
                                        bricks[i] = false;
                                        score += 20;
                                        scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
                                    }
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
                            renderTextureText(scoreText, 35, 27, renderer);
                            renderTextureText(liveCountText, 351, 27, renderer);
                            renderTextureText(highScoreText, 594, 27, renderer);

                            for (int i = 0; i < ROW*COL; i++) {
                                if (bricks[i]) {
                                    setBricks(i, brick);
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
                                            liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
                                            resetBricks(bricks);
                                            resetBrickHits(brickHits);
                                            gameState = GAME;
                                            highScore = max(highScore, score);
                                            score = 0;
                                            scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
                                            saveHighScore("assets/highScore.txt", highScore);
                                            loadHighScore("assets/highScore.txt", highScore);
                                            highScoreText = renderText( "HIGH SCORE: " + to_string(highScore) , liveCountFont, color, renderer);
                                        } else if ( posX >= 353 && posX <= 646 && posY >= 594 && posY <= 648 ) {
                                            gameState = QUIT;
                                        }
                                    }
                                }

                                SDL_RenderClear(renderer);
                                renderTexture(gameOverImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                SDL_RenderPresent(renderer);
                            }
                        }
                    }
                    //hard
                    if ( hard ) {
                        //update double speed
                        vX *= 2;
                        vY *= 2;
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

                            if ( isWinning(bricks) ) {
                                gameState = WIN;

                                while (gameState == WIN) {
                                    SDL_Event winEvent;
                                    while ( SDL_PollEvent(&winEvent) != 0 ) {
                                        if (winEvent.type == SDL_QUIT) {
                                            gameState = QUIT;
                                        } else if (winEvent.type == SDL_MOUSEBUTTONDOWN) {
                                            int posX = winEvent.button.x;
                                            int posY = winEvent.button.y;
                                            SDL_GetMouseState(&posX, &posY);
                                            cerr << posX << ", " << posY << endl;

                                            if ( posX >= 128 && posX <= 458 && posY >= 563 && posY <= 636 ) {
                                                liveCount = 3;
                                                liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
                                                resetBricks(bricks);
                                                resetBrickHits(brickHits);
                                                setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5, ballRect);
                                                gameState = GAME;
                                                highScore = max(highScore, score);
                                                score = 0;
                                                scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
                                                saveHighScore("assets/highScore.txt", highScore);
                                                loadHighScore("assets/highScore.txt", highScore);
                                                highScoreText = renderText( "HIGH SCORE: " + to_string(highScore) , liveCountFont, color, renderer);
                                            } else if ( posX >= 538 && posX <= 869 && posY >= 564 && posY <= 635 ) {
                                                gameState = QUIT;
                                            }
                                        }
                                    }

                                    SDL_RenderClear(renderer);
                                    renderTexture(winImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                    SDL_RenderPresent(renderer);
                                }
                            }

                            if ( ballRect.y + ballRect.h >= SCREEN_HEIGHT ) {
                                liveCount--;
                                if (liveCount == 2) liveCountText =  renderText("LIVES: 2", liveCountFont, color, renderer);
                                else if (liveCount == 1) liveCountText =  renderText("LIVES: 1", liveCountFont, color, renderer);
                                else if (liveCount == 0) gameState = GAME_OVER;
                                setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5, ballRect);
                                renderTextureText(liveCountText, 500, 500, renderer);
                                waitingForClick = false;
                            }
                            
                            if (handleBallPaddleCollision(ballRect, paddle1)) {
                                playChunk(ballCollisionPaddle);
                            }
                            
                            for(int i=0; i<COL*ROW; i++) {
                                setBricks(i, brick);
                                if(SDL_HasIntersection( &ballRect, &brick ) && bricks[i]) {
                                    brickHits[i]++;
                                    playChunk(brickCollisionBall);
                                    if (brickHits[i] >= 3) {
                                        bricks[i] = false;
                                        score += 20;
                                        scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
                                    }
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
                            renderTextureText(scoreText, 35, 27, renderer);
                            renderTextureText(liveCountText, 351, 27, renderer);
                            renderTextureText(highScoreText, 594, 27, renderer);

                            for (int i = 0; i < ROW*COL; i++) {
                                if (bricks[i]) {
                                    setBricks(i, brick);
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
                                            liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
                                            resetBricks(bricks);
                                            resetBrickHits(brickHits);
                                            gameState = GAME;
                                            highScore = max(highScore, score);
                                            score = 0;
                                            scoreText = renderText("SCORE: " + to_string(score), scoreFont, color, renderer);
                                            saveHighScore("assets/highScore.txt", highScore);
                                            loadHighScore("assets/highScore.txt", highScore);
                                            highScoreText = renderText( "HIGH SCORE: " + to_string(highScore) , liveCountFont, color, renderer);
                                        } else if ( posX >= 353 && posX <= 646 && posY >= 594 && posY <= 648 ) {
                                            gameState = QUIT;
                                        }
                                    }
                                }

                                SDL_RenderClear(renderer);
                                renderTexture(gameOverImage, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, renderer);
                                SDL_RenderPresent(renderer);
                            }
                        }
                    }

                }
            }
        }
    }
    quitSDL(window, renderer);
    return 0;
}