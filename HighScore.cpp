#include "HighScore.h"

void loadHighScore(const char* path, int &highScore) {
    ifstream infile(path);
    if (infile.is_open()) {
        infile >> highScore;
        infile.close();
    } else {
        cout << "unable to open file " << path << endl;
    }
}

void saveHighScore(const char* path, int &highScore) {
    ofstream outfile(path);
    if (outfile.is_open()) {
        outfile << highScore << endl;
    } else {
        cout << "unable to save highScore in " << path << endl;
    }
}