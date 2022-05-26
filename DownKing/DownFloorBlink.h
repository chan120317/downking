#pragma once
#include "DownFloorBase.h"

class DownFloorBlink : public DownFloorBase
{
public:
	DownFloorBlink();
	~DownFloorBlink();
	void init();
	void process(Uint64 currentTick);
	void render(const GameContext* ctx, CoordinateConverter* conv);

private:
	Uint64 lastTick;
	bool BLINK;
	double holeLeft;
};