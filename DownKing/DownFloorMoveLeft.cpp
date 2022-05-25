#include "DownFloorMoveLeft.h"
#include "common.h"
#include "random.h"
#include "iostream"

constexpr double MOVESPEED = 0.5;

DownFloorMoveLeft::DownFloorMoveLeft():lastTick(0), MOVESPEED(0.5), holeLeft(0)
{

}

DownFloorMoveLeft::~DownFloorMoveLeft()
{

}

void DownFloorMoveLeft::init()
{
	lastTick = 0;
	MOVESPEED = randDouble(5,30);
	auto left = randDouble(0, GAME_SCREEN_WIDTH);

	holeLeft = left;
}

void DownFloorMoveLeft::process(Uint64 currentTick)
{
	const auto t = double(currentTick - lastTick)/100;

	lines.clear();
	holeLeft -= MOVESPEED * t;

	if (holeLeft < 0) 
		holeLeft = GAME_SCREEN_WIDTH + holeLeft;
	
	if (holeLeft > GAME_SCREEN_WIDTH - 100.0) {
		lines.push_back(DownInfoFloor(holeLeft + 100 - GAME_SCREEN_WIDTH, holeLeft, -MOVESPEED));
	}
	else {
		lines.push_back(DownInfoFloor(0, holeLeft, -MOVESPEED));
		lines.push_back(DownInfoFloor(holeLeft + 100, GAME_SCREEN_WIDTH, -MOVESPEED));
	}

	
	lastTick = currentTick;
}

void DownFloorMoveLeft::render(const GameContext* ctx, CoordinateConverter* conv)
{
	auto leftBlock1 = ctx->resources->images.get(ImageResources::leftBlock1);
	auto leftBlockleft = ctx->resources->images.get(ImageResources::leftBlockleft);
	auto leftBlockright = ctx->resources->images.get(ImageResources::leftBlockright);
	
	if (lines.size() == 1) {
		auto newY = conv->convertY(posY);
		double x = lines[0].left;
		ctx->renderer->drawImage(leftBlockleft, x, newY, leftBlockleft->width, leftBlockleft->height);
		x += leftBlock1->width;
		while (x<lines[0].right- leftBlock1->width)
		{
			ctx->renderer->drawImage(leftBlock1, x, newY, leftBlock1->width, leftBlock1->height);
			x += leftBlock1->width;
		}
		ctx->renderer->drawImage(leftBlockright, x, newY, leftBlockright->width, leftBlockright->height);

	}
	else {
		for (const auto& line : lines) {
			auto newY = conv->convertY(posY);
			ctx->renderer->drawLine(line.left, newY, line.right, newY);

			if (line.right == GAME_SCREEN_WIDTH) {
				double x = line.left;
				ctx->renderer->drawImage(leftBlockleft, x, newY, leftBlockleft->width, leftBlockleft->height);
				x += leftBlock1->width;
				while (x < GAME_SCREEN_WIDTH)
				{
					//양쪽 다 안막힌거 랜더링
					ctx->renderer->drawImage(leftBlock1, x, newY, leftBlock1->width, leftBlock1->height);
					x += leftBlock1->width;
				}
			}
			else {
				double x = line.right - leftBlock1->width;
				//오른쪽 막힌거 랜더링
				ctx->renderer->drawImage(leftBlockright, x, newY, leftBlockright->width, leftBlockright->height);
				x -= leftBlock1->width;
				while (x > -leftBlock1->width)
				{
					//양쪽 다 안막힌거 랜더링
					ctx->renderer->drawImage(leftBlock1, x, newY, leftBlock1->width, leftBlock1->height);
					x -= leftBlock1->width;
				}
			}


		}
	}
}
