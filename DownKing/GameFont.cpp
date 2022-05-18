#include "GameFont.h"

#include <iostream>
#include <atlstr.h>

GameFont::GameFont(const char* path, int fontSize)
{
	this->font = TTF_OpenFont(path, fontSize);
	if (!this->font) {
		std::cout << "Error loading font: " << TTF_GetError() << std::endl;
	}
}

GameFont::~GameFont()
{
	TTF_CloseFont(this->font);
}

SDL_Surface* GameFont::createSurface(const char* content, SDL_Color color)
{
	//char* str = CW2A(CA2W(content), CP_UTF8);
	//wchar_t* str = CA2W(content);

	auto surface = TTF_RenderText_Solid(this->font, content, color);
	//auto surface = TTF_RenderUNICODE_Solid(this->font, str, color);
	//auto surface = TTF_RenderUTF8_Solid(this->font, str, color);
	return surface;
}

SDL_Surface* GameFont::createSurfaceUnicode(const wchar_t* content, SDL_Color color)
{
	auto surface = TTF_RenderUNICODE_Blended(this->font, (Uint16*)content, color);
	return surface;
}
