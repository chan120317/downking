#pragma once
#include "SDL.h"
#include "SDL_TTF.h"

class GameFont
{
public:
	GameFont(const char* path, int fontSize);
	~GameFont();

	SDL_Surface* createSurface(const char* content, SDL_Color color);
	SDL_Surface* createSurfaceUnicode(const wchar_t* content, SDL_Color color);
private:
	TTF_Font* font;
};

