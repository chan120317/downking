#pragma once
#include "DownFloorBase.h"

class DownFloorMoveRight : public DownFloorBase
{
public:
	DownFloorMoveRight();
	~DownFloorMoveRight();
	void init();
	void process(Uint64 currentTick);
	void render(const GameContext* ctx, CoordinateConverter* conv);

private:
	Uint64 lastTick;
	double MOVESPEED;
	double holeLeft;
};

