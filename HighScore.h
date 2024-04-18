#ifndef HighScore__H 
#define HighScore__H

#include <iostream>
#include <fstream>

using namespace std;

void loadHighScore(const char* path, int &highScore);

void saveHighScore(const char* path, int &highScore);

#endif