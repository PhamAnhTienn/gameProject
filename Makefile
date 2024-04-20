all:
	g++ -I src/include -L src/lib -o main main.cpp SDL_utils.cpp Paddle.cpp Ball.cpp Brick.cpp image.cpp Sound.cpp Text.cpp HighScore.cpp game.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
