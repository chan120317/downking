#pragma once
#include <vector>
#include "DownInfoFloor.h"
#include "CoordinateConverter.h"
#include "GameContext.h"

class DownFloorBase
{
public:
	virtual ~DownFloorBase() {};
	virtual void init() {};
	virtual void process(Uint64 currentTick) = 0;
	virtual void render(const GameContext* ctx, CoordinateConverter* conv) = 0;

	double posY;
	std::vector<DownInfoFloor> lines;
};

