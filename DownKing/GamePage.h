#pragma once
#include "util.h"
#include "IPage.h"
#include "GameContext.h"

class GamePage: public IPage
{
public:
	GamePage(const GameContext* ctx);
	~GamePage();

	void init();
	void tick(Uint64 currentTick);

	void onKeyDown(SDL_Keycode keyCode);
private:
	const GameContext* ctx;

	void process(Uint64 currentTick);
	void render();


	Point<double> playerPos;
	Point<double> camera;

	Point<double> playerV, playerA;
};

