#ifndef IMAGE__H 
#define IMAGE__H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
using namespace std;

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);

void renderTexture(SDL_Texture *texture, int x, int y, int w, int h, SDL_Renderer* renderer);

void renderTextureText(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer);

#endif
