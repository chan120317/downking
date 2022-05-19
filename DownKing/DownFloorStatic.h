#pragma once
#include "DownFloorBase.h"

class DownFloorStatic : public DownFloorBase
{
public:
	DownFloorStatic();
	~DownFloorStatic();
	void init();
	void process(Uint64 currentTick);
	void render(GameRenderer* renderer, CoordinateConverter* conv);

	
};

