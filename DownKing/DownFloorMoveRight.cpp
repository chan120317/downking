#include "DownFloorMoveRight.h"
#include "const.h"
#include "common.h"
#include "random.h"


DownFloorMoveRight::DownFloorMoveRight() :lastTick(0), MOVESPEED(0.5), holeLeft(0)
{

}

DownFloorMoveRight::~DownFloorMoveRight()
{

}

void DownFloorMoveRight::init()
{
	lastTick = 0;
	MOVESPEED = randDouble(GAME_FLOOR_MOVE_MIN_SPEED, GAME_FLOOR_MOVE_MAX_SPEED);
	auto left = randDouble(0, GAME_SCREEN_WIDTH);

	holeLeft = left;
}

void DownFloorMoveRight::process(Uint64 currentTick)
{
	const auto t = double(currentTick - lastTick) / 100;

	lines.clear();
	holeLeft += MOVESPEED * t;

	if (holeLeft > GAME_SCREEN_WIDTH)
		holeLeft = 0;

	if (holeLeft > GAME_SCREEN_WIDTH - GAME_FLOOR_HOLE_SIZE) {
		lines.push_back(DownInfoFloor(holeLeft + GAME_FLOOR_HOLE_SIZE - GAME_SCREEN_WIDTH, holeLeft, -MOVESPEED));
	}
	else {
		lines.push_back(DownInfoFloor(0, holeLeft, -MOVESPEED));
		lines.push_back(DownInfoFloor(holeLeft + GAME_FLOOR_HOLE_SIZE, GAME_SCREEN_WIDTH, -MOVESPEED));
	}


	lastTick = currentTick;
}

void DownFloorMoveRight::render(const GameContext* ctx, CoordinateConverter* conv)
{
	auto rightBlock1 = ctx->resources->images.get(ImageResources::rightBlock1);
	auto rightBlockleft = ctx->resources->images.get(ImageResources::rightBlockleft);
	auto rightBlockright = ctx->resources->images.get(ImageResources::rightBlockright);

	if (lines.size() == 1) {
		auto newY = conv->convertY(posY);
		double x = lines[0].left;
		ctx->renderer->drawImage(rightBlockleft, x, newY, rightBlockleft->width, rightBlockleft->height);
		x += rightBlock1->width;
		while (x < lines[0].right - rightBlock1->width)
		{
			ctx->renderer->drawImage(rightBlock1, x, newY, rightBlock1->width, rightBlock1->height);
			x += rightBlock1->width;
		}
		ctx->renderer->drawImage(rightBlockright, x, newY, rightBlockright->width, rightBlockright->height);

	}
	else {
		for (const auto& line : lines) {
			auto newY = conv->convertY(posY);
			ctx->renderer->drawLine(line.left, newY, line.right, newY);

			if (line.right == GAME_SCREEN_WIDTH) {
				double x = line.left;
				ctx->renderer->drawImage(rightBlockleft, x, newY, rightBlockleft->width, rightBlockleft->height);
				x += rightBlock1->width;
				while (x < GAME_SCREEN_WIDTH)
				{
					//양쪽 다 안막힌거 랜더링
					ctx->renderer->drawImage(rightBlock1, x, newY, rightBlock1->width, rightBlock1->height);
					x += rightBlock1->width;
				}
			}
			else {
				double x = line.right - rightBlock1->width;
				//오른쪽 막힌거 랜더링
				ctx->renderer->drawImage(rightBlockright, x, newY, rightBlockright->width, rightBlockright->height);
				x -= rightBlock1->width;
				while (x > -rightBlock1->width)
				{
					//양쪽 다 안막힌거 랜더링
					ctx->renderer->drawImage(rightBlock1, x, newY, rightBlock1->width, rightBlock1->height);
					x -= rightBlock1->width;
				}
			}


		}
	} 
}
