#pragma once
#include "SDL.h"

class IPage
{
public:
	virtual ~IPage() {};
	virtual void init() = 0;
	virtual void fini() {};
	virtual void tick(Uint64 currentTick) = 0;
	virtual void onKeyDown(SDL_Keycode keyCode) {};
	virtual void onKeyUp(SDL_Keycode keyCode) {};
	virtual void onMouseLeftDown(int x, int y) {};
	virtual void onMouseRightDown(int x, int y) {};
};
