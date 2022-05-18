#pragma once
#include "IPage.h"
#include "GameContext.h"

class EndingPage: public IPage
{
public:
	EndingPage(const GameContext* ctx);
	~EndingPage();

	void init();
	void tick(Uint64 currentTick);

	void onMouseLeftDown(int x, int y);
private:
	const GameContext* ctx;
};

