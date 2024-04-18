#ifndef TEXT__H 
#define TEXT__H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
using namespace std;

TTF_Font* loadFont(const char* path, int size);

SDL_Texture* renderText(string text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer);

#endif



