#include "GameRenderer.h"

GameRenderer::GameRenderer(SDL_Renderer* renderer) : sdlRen(renderer)
{
}

void GameRenderer::clear()
{
	SDL_RenderClear(this->sdlRen);
}

void GameRenderer::render()
{
	SDL_RenderPresent(this->sdlRen);
}

void GameRenderer::setBackground(SDL_Color color)
{
	SDL_SetRenderDrawColor(this->sdlRen, color.r, color.g, color.b, color.a);
}

void GameRenderer::drawText(GameFont* font, std::string txt, int x, int y, SDL_Color color)
{
	auto surface = font->createSurface(txt.c_str(), color);
	auto texture = SDL_CreateTextureFromSurface(this->sdlRen, surface);

	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = surface->w;
	src.h = surface->h;

	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	SDL_RenderCopy(this->sdlRen, texture, &src, &dest);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void GameRenderer::drawTextUnicode(GameFont* font, std::wstring txt, int x, int y, SDL_Color color)
{
	auto surface = font->createSurfaceUnicode(txt.c_str(), color);
	auto texture = SDL_CreateTextureFromSurface(this->sdlRen, surface);

	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = surface->w;
	src.h = surface->h;

	dest.x = x;
	dest.y = y;
	dest.w = surface->w;
	dest.h = surface->h;

	SDL_RenderCopy(this->sdlRen, texture, &src, &dest);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void GameRenderer::drawImageRaw(GameImage* image, int x, int y)
{
	SDL_Rect src, dest;

	src.x = 0;
	src.y = 0;
	src.w = image->width;
	src.h = image->height;

	dest.x = x;
	dest.y = y;
	dest.w = image->width;
	dest.h = image->height;

	SDL_RenderCopy(this->sdlRen, image->getTexture(this->sdlRen), &src, &dest);
}

void GameRenderer::drawImage(GameImage* image, int x, int y, int w, int h)
{
	SDL_Rect src, dest;

	src.x = 0;
	src.y = 0;
	src.w = image->width;
	src.h = image->height;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_RenderCopy(this->sdlRen, image->getTexture(this->sdlRen), &src, &dest);
}

void GameRenderer::drawImageRotate(GameImage* image, int x, int y, int w, int h, double angle, int centerX, int centerY)
{
	SDL_Rect src, dest;

	src.x = 0;
	src.y = 0;
	src.w = image->width;
	src.h = image->height;

	dest.x = x;
	dest.y = y;
	dest.w = w;
	dest.h = h;

	SDL_Point center;
	center.x = centerX;
	center.y = centerY;

	SDL_RenderCopyEx(this->sdlRen, image->getTexture(this->sdlRen), &src, &dest, angle, &center, SDL_FLIP_NONE);
}
