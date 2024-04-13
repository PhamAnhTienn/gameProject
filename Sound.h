#ifndef SOUND__H 
#define SOUND__H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
using namespace std;

Mix_Music* loadMusic(const char* path);

Mix_Chunk* loadSound(const char* path);

void playMusic(Mix_Music *gMusic);

void playChunk(Mix_Chunk* gChunk);

void stopBackgroundMusic();

#endif