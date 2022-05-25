#pragma once
#include "DownFloorBase.h"

class DownFloorMoveLeft : public DownFloorBase
{
public:
	DownFloorMoveLeft();
	~DownFloorMoveLeft();
	void init();
	void process(Uint64 currentTick);
	void render(const GameContext* ctx, CoordinateConverter* conv);

private:
	Uint64 lastTick;
	double MOVESPEED;
	double holeLeft;
};

