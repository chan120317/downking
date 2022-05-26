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
	auto left = randDouble(10, GAME_SCREEN_WIDTH - 150.0);
	lines.push_back(DownInfoFloor(0, left, 0));
	lines.push_back(DownInfoFloor(left + 100, GAME_SCREEN_WIDTH, 0));
}

void DownFloorStatic::process(Uint64 currentTick)
{

}

void DownFloorStatic::render(const GameContext* ctx, CoordinateConverter* conv)
{

	auto stopBlock1 = ctx->resources->images.get(ImageResources::stopBlock1);
	auto stopBlockleft = ctx->resources->images.get(ImageResources::stopBlockleft);
	auto stopBlockright = ctx->resources->images.get(ImageResources::stopBlockright);
	for (const auto& line : lines) {
		auto newY = conv->convertY(posY);
		ctx->renderer->drawLine(line.left, newY, line.right, newY);

		if (line.right == GAME_SCREEN_WIDTH) {
			double x = line.left;
			ctx->renderer->drawImage(stopBlockleft, x, newY, stopBlockleft->width, stopBlockleft->height);
			x += 32;
			while (x < GAME_SCREEN_WIDTH)
			{
				//양쪽 다 안막힌거 랜더링
				ctx->renderer->drawImage(stopBlock1, x, newY, stopBlock1->width, stopBlock1->height);
				x += 32;
			}
		}
		else {
			double x = line.right - 32;
			//오른쪽 막힌거 랜더링
			ctx->renderer->drawImage(stopBlockright, x, newY, stopBlockright->width, stopBlockright->height);
			x -= 32;
			while (x > -32)
			{
				//양쪽 다 안막힌거 랜더링
				ctx->renderer->drawImage(stopBlock1, x, newY, stopBlock1->width, stopBlock1->height);
				x -= 32;
			}
		}
		

	}
}
