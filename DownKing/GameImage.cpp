#include "GameImage.h"
#include <iostream>

GameImage::GameImage(const char* path, int width, int height) : width(width), height(height), texture(nullptr)
{
	SDL_Surface* img = IMG_Load(path);
	if (img == nullptr) {
		std::cout << "Failed to load image: " << IMG_GetError() << std::endl;
		throw "Failed to load Image";
	}
	this->image = img;
}

GameImage::~GameImage()
{
	SDL_FreeSurface(this->image);
	if (!this->texture) {
		SDL_DestroyTexture(this->texture);

	}
}

SDL_Texture* GameImage::getTexture(SDL_Renderer* renderer)
{
	if (!this->texture) {
		this->texture = SDL_CreateTextureFromSurface(renderer, this->image);
	}
	return this->texture;
}
