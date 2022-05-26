#pragma once
#include <deque>
#include <tuple>
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
	void onKeyUp(SDL_Keycode keyCode);
	void onMouseLeftDown(int x, int y);
private:
	const GameContext* ctx;

	void process(Uint64 currentTick);
	void render();

	std::tuple<bool, double, double> floorCheck(double newPlayerY, double newPlayerX, double lastPlayerY);

	Uint64 lastTick;

	bool isGameOver;

	Point<double> playerPos;
	Point<double> camera;

	Point<double> playerV, playerA;

	std::deque<DownFloorBase*> floors;

	int playerDirection;

	
};

