#include "Text.h"
#include <iostream>

TTF_Font* loadFont(const char* path, int size) {
    TTF_Font* gFont = TTF_OpenFont( path, size );
    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
    }
    return gFont;
}

SDL_Texture* renderText(string text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer)
{
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.c_str(), textColor );
    if( textSurface == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( texture == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface( textSurface );
    return texture;
}


