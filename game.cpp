#include "game.h"
#include "SDL_utils.h"
#include "image.h"
#include "Sound.h"
#include "Text.h"
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "HighScore.h"

Paddle paddle1(SCREEN_WIDTH / 2 - 88, SCREEN_HEIGHT - 30, 200, 15);
void Game::initGame() {
    resetBricks(bricks);
    setBallRect(SCREEN_WIDTH / 2 + 2, SCREEN_HEIGHT / 2 + 210, 5, ballRect);
    initSDL(window, renderer, 1000, 700, WINDOW_TITLE);
    menuImage = loadTexture("assets/menuImage.png", renderer);
    optionImage = loadTexture("assets/optionImage.png", renderer);
    easyImage = loadTexture("assets/easyImage.png", renderer);
    mediumImage = loadTexture("assets/mediumImage.png", renderer);
    hardImage = loadTexture("assets/hardImage.png", renderer);
    backgroundImage = loadTexture("assets/backgroundImage.png", renderer);
    gameOverImage = loadTexture("assets/gameOverImage.png", renderer);
    winImage = loadTexture("assets/winImage.png", renderer);
    cursorImage = loadTexture("assets/cursor_hand.png", renderer);
    paddleImage = loadTexture("assets/paddleRed.png", renderer);
    ballImage = loadTexture("assets/ballImage.png", renderer);

    brickRed = loadTexture("assets/element_red_rectangle.png", renderer);
    brickYellow = loadTexture("assets/element_yellow_rectangle.png", renderer);
    brickGreen = loadTexture("assets/element_green_rectangle.png", renderer);
    brickBlue = loadTexture("assets/element_blue_rectangle.png", renderer);
    brickPurple = loadTexture("assets/element_purple_rectangle.png", renderer);
    brickGrey = loadTexture("assets/element_grey_rectangle.png", renderer);

    menuSound = loadMusic("assets/backgroundMusic.mp3");
    ballCollisionPaddle = loadSound("assets/collisionsound.wav");
    brickCollisionBall = loadSound("assets/brickCollision.mp3");

    liveCountFont = loadFont("assets/GayoLand-Rounded.ttf", 36);
    highScoreFont = loadFont("assets/GayoLand-Rounded.ttf", 36);
    scoreFont = loadFont("assets/GayoLand-Rounded.ttf", 36);
    color = {255, 0, 255, 0}; 

    liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
    scoreText =  renderText( "SCORE: " + to_string(score) , liveCountFont, color, renderer);
    highScoreText = renderText( "HIGH SCORE: " + to_string(highScore) , liveCountFont, color, renderer);
}

void Game::winGame(bool medium, bool hard) {
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
                    cout << posX << ", " << posY << endl;

                    if ( posX >= 128 && posX <= 458 && posY >= 563 && posY <= 636 ) {
                        liveCount = 3;
                        liveCountText = renderText("LIVES: 3", liveCountFont, color, renderer);
                        resetBricks(bricks);
                        if ( medium || hard ) resetBrickHits(brickHits);
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
}

void Game::playAgain(bool medium, bool hard) {
    while (gameState == GAME_OVER) {
        SDL_Event finalEvent;
        while ( SDL_PollEvent(&finalEvent) != 0 ) {
            if (finalEvent.type == SDL_QUIT) {
                gameState = QUIT;
            } else if (finalEvent.type == SDL_MOUSEBUTTONDOWN) {
                int posX = finalEvent.button.x;
                int posY = finalEvent.button.y;
                SDL_GetMouseState(&posX, &posY);
                cout << posX << ", " << posY << endl;

                if ( posX >= 353 && posX <= 646 && posY >= 499 && posY <= 552 ) {
                    liveCount = 3;
                    liveCountText =  renderText("LIVES: 3", liveCountFont, color, renderer);
                    resetBricks(bricks);
                    if ( medium || hard ) resetBrickHits(brickHits);
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

void Game::optionsGame() {
    while (gameState == OPTIONS) {
        SDL_Event optionEvent;
        while ( SDL_PollEvent(&optionEvent) != 0 ) {
            if (optionEvent.type == SDL_QUIT) gameState = QUIT;
            if (optionEvent.type == SDL_MOUSEBUTTONDOWN) {
                int posX = optionEvent.button.x;
                int posY = optionEvent.button.y;
                SDL_GetMouseState(&posX, &posY);

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

void Game::easyGame() {
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
                cout << posX << ", " << posY << endl;
                waitingForClick = true;
            }
        }

        if (waitingForClick) move(ballRect);
                            
        //winning
        winGame(medium, hard);

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
        playAgain(medium, hard);
    }
}

void Game::mediumGame() {
    while (gameState == GAME) { 
        SDL_Event mediumEvent;
        while ( SDL_PollEvent(&mediumEvent) != 0 )
        {
            if (mediumEvent.type == SDL_QUIT)
            {
                gameState = QUIT;
            }
            else if( mediumEvent.type == SDL_KEYDOWN )
            {
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

                bool moveLeft = currentKeyStates[SDL_SCANCODE_LEFT];
                bool moveRight = currentKeyStates[SDL_SCANCODE_RIGHT];

                paddleMove(paddle1, moveLeft, moveRight);
            } else if (mediumEvent.type == SDL_MOUSEBUTTONDOWN && !waitingForClick) {
                int posX = mediumEvent.button.x;
                int posY = mediumEvent.button.y;
                SDL_GetMouseState(&posX, &posY);
                cerr << posX << ", " << posY << endl;
                waitingForClick = true;
            }
        }

        if (waitingForClick) move(ballRect);
                            
        //winning
        winGame(medium, hard);

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
        playAgain(medium, hard);
    }
}

void Game::hardGame() {
    //update double speed
    vX *= 2;
    vY *= 2;
    while (gameState == GAME) { 
        SDL_Event hardEvent;
        while ( SDL_PollEvent(&hardEvent) != 0 )
        {
            if (hardEvent.type == SDL_QUIT)
            {
                gameState = QUIT;
            }
            else if( hardEvent.type == SDL_KEYDOWN )
            {
                const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

                bool moveLeft = currentKeyStates[SDL_SCANCODE_LEFT];
                bool moveRight = currentKeyStates[SDL_SCANCODE_RIGHT];

                paddleMove(paddle1, moveLeft, moveRight);
            } else if (hardEvent.type == SDL_MOUSEBUTTONDOWN && !waitingForClick) {
                int posX = hardEvent.button.x;
                int posY = hardEvent.button.y;
                SDL_GetMouseState(&posX, &posY);
                cerr << posX << ", " << posY << endl;
                waitingForClick = true;
            }
        }

        if (waitingForClick) move(ballRect);
                            
        //winning
        winGame(medium, hard);

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
        playAgain(medium, hard);
    }
}

void Game::runningGame() {
    initGame();
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
                    optionsGame();
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
                        easyGame();
                    }
                    //medium
                    if ( medium ) {
                        mediumGame();
                    }
                    //hard
                    if ( hard ) {
                        hardGame();
                    }

                }
            }
        }
    }
    quitSDL(window, renderer);
}