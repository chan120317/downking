#pragma once
#include "IPage.h"
#include "GameContext.h"

class IntroPage: public IPage
{
public:
	IntroPage(const GameContext* ctx);
	~IntroPage();

	void init();
	void tick(Uint64 currentTick);

	void onMouseLeftDown(int x, int y);
private:
	const GameContext* ctx;
};

