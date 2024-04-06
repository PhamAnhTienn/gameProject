#include "image.h"
#include <iostream>

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());
    }

	return texture;
}

void renderTexture(SDL_Texture *texture, int x, int y, int w, int h, SDL_Renderer* renderer)
{
	SDL_Rect dest = { x, y, w, h };
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

