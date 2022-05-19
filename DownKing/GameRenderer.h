#pragma once
#include <string>
#include "SDL.h"
#include "GameFont.h"
#include "GameImage.h"


class GameRenderer
{
public:
	GameRenderer(SDL_Renderer* renderer);

	void clear();
	void render();
	void setBackground(SDL_Color color);
	void drawText(GameFont* font, std::string txt, int x, int y, SDL_Color color);
	void drawTextUnicode(GameFont* font, std::wstring txt, int x, int y, SDL_Color color);
	void drawImageRaw(GameImage* image, int x, int y);
	void drawImage(GameImage* image, int x, int y, int w, int h);
	void drawImageRotate(GameImage* image, int x, int y, int w, int h, double angle, int centerX, int centerY);
	void drawLine(int x1, int y1, int x2, int y2);
private:
	SDL_Renderer* sdlRen;
};

