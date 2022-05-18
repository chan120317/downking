#pragma once
#include "SDL_image.h"

class GameImage {
public:
	GameImage(const char* path, int width, int height);
	~GameImage();

	SDL_Texture* getTexture(SDL_Renderer* renderer);

	const int width, height;
private:
	SDL_Surface* image;
	SDL_Texture* texture;
};