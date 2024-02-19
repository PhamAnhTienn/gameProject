all:
	g++ -I src/include -L src/lib -o main main.cpp -lmingw32 -lSDL2main -lSDL2
	
	//lưu ý khi có nhiều file header khác nhau thì chạy như trên sẽ không được phải thêm các file header đó vào sau cái main.cpp chữ
	main đằng trươc main.cpp tức là khi gọi thì output sẽ gọi từ file đứng sau từ main đó 
	cú pháp gọi :
	g++ -I src/include -L src/lib -o main main.cpp file-dinh-nghia-cac-header.cpp ... -lmingw32 -lSDL2main -lSDL2

	VI DU:

	g++ -I src/include -L src/lib -o main main.cpp SDL_utils.cpp Image.cpp Paddle.cpp Ball.cpp Sound.cpp Text.cpp Time.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

