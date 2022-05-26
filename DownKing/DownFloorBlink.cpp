#include "DownFloorBlink.h"
#include "const.h"
#include "common.h"
#include "random.h"
#include "iostream"

DownFloorBlink::DownFloorBlink() :lastTick(0), BLINK(0), holeLeft(0)
{

}

DownFloorBlink::~DownFloorBlink()
{

}

void DownFloorBlink::init()
{
	lastTick = 0;
	BLINK = false;
	auto left = randDouble(0, GAME_SCREEN_WIDTH-296.0);

	holeLeft = left;
}

void DownFloorBlink::process(Uint64 currentTick)
{
	lines.clear();
	if (BLINK == true) {
		lines.push_back(DownInfoFloor(0, holeLeft, 0));
		lines.push_back(DownInfoFloor(holeLeft + 296, GAME_SCREEN_WIDTH, 0));
	}
	else {
		lines.push_back(DownInfoFloor(holeLeft, holeLeft + 296, 0));
	}

	if (currentTick - lastTick > 1000) {
		if (BLINK == false) 
			BLINK = true;
		else 
			BLINK = false;
		lastTick = currentTick;
	}

}

void DownFloorBlink::render(const GameContext* ctx, CoordinateConverter* conv)
{
	auto blinkBlock1 = ctx->resources->images.get(ImageResources::blinkBlock1);
	auto blinkBlockleft = ctx->resources->images.get(ImageResources::blinkBlockleft);
	auto blinkBlockright = ctx->resources->images.get(ImageResources::blinkBlockright);

	if (BLINK == true) {
		for (const auto& line : lines) {
			auto newY = conv->convertY(posY);
			ctx->renderer->drawLine(line.left, newY, line.right, newY);

			if (line.right == GAME_SCREEN_WIDTH) {
				double x = line.left;
				ctx->renderer->drawImage(blinkBlockleft, x, newY, blinkBlockleft->width, blinkBlockleft->height);
				x += blinkBlock1->width;
				while (x < GAME_SCREEN_WIDTH)
				{
					//양쪽 다 안막힌거 랜더링
					ctx->renderer->drawImage(blinkBlock1, x, newY, blinkBlock1->width, blinkBlock1->height);
					x += blinkBlock1->width;
				}
			}
			else {
				double x = line.right - blinkBlock1->width;
				//오른쪽 막힌거 랜더링
				ctx->renderer->drawImage(blinkBlockright, x, newY, blinkBlockright->width, blinkBlockright->height);
				x -= blinkBlock1->width;
				while (x > -blinkBlock1->width)
				{
					//양쪽 다 안막힌거 랜더링
					ctx->renderer->drawImage(blinkBlock1, x, newY, blinkBlock1->width, blinkBlock1->height);
					x -= blinkBlock1->width;
				}
			}
		}
	}
	else {
		for (const auto& line : lines) {
			auto newY = conv->convertY(posY);
			ctx->renderer->drawLine(line.left, newY, line.right, newY);
		
			double x = line.left;
			ctx->renderer->drawImage(blinkBlockleft, x, newY, blinkBlockleft->width, blinkBlockleft->height);
			x += blinkBlockleft->width;
			while (x<line.right - blinkBlockright->width)
			{
				ctx->renderer->drawImage(blinkBlock1, x, newY, blinkBlock1->width, blinkBlock1->height);
				x += blinkBlock1->width;
			}
			ctx->renderer->drawImage(blinkBlockright, x, newY, blinkBlockright->width, blinkBlockright->height);

		}
	}
}
