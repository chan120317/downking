#pragma once
#include <deque>
#include "util.h"
#include "IPage.h"
#include "GameContext.h"
#include "DownFloorBase.h"

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

	Uint64 lastTick;

	Point<double> playerPos;
	Point<double> camera;

	Point<double> playerV, playerA;

	std::deque<DownFloorBase*> floors;
};

