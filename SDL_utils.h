#ifndef SDL_UTILS__H 
#define SDL_USTILS__H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

void logSDLError(std::ostream& os, const std::string &msg, bool fatal);

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const string &WINDOW_TITLE);

void initSDLTTF(TTF_Font* font);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

void waitUntilKeyPressed();

#endif