#include "DownFloorStatic.h"
#include "common.h"
#include "random.h"

DownFloorStatic::DownFloorStatic()
{

}

DownFloorStatic::~DownFloorStatic()
{

}

void DownFloorStatic::init()
{
	auto left = randDouble(0, GAME_SCREEN_WIDTH - 150.0);
	lines.push_back(DownInfoFloor(0, left, 0));
	lines.push_back(DownInfoFloor(left + 100, GAME_SCREEN_WIDTH, 0));
}

void DownFloorStatic::process(Uint64 currentTick)
{

}

void DownFloorStatic::render(GameRenderer* renderer, CoordinateConverter* conv)
{
	for (const auto& line : lines) {
		auto newY = conv->convertY(posY);
		renderer->drawLine(line.left, newY, line.right, newY);
	}
}
