#include <iostream>
#include "GamePage.h"
#include "CoordinateConverter.h"
#include "DownFloorStatic.h"

constexpr double GAME_GRAVITY = 3.0;
constexpr double GAME_PLAYER_MAX_V_Y = 30.0;

constexpr double GAME_PLAYER_W = 32.0;
constexpr double GAME_PLAYER_H = 32.0;

GamePage::GamePage(const GameContext* ctx) : 
	ctx(ctx),
	lastTick(0)
{
}

GamePage::~GamePage()
{
}

void GamePage::init()
{
	playerPos = Point<double>(50, 50);
	playerV = Point<double>(0, 0);
	playerA = Point<double>(0, 0);

	auto floor = new DownFloorStatic();
	floor->posY = 200;
	floors.push_back(floor);
	floor->init();
}

void GamePage::tick(Uint64 currentTick)
{
	if (lastTick == 0) {
		lastTick = currentTick;
		return;
	}
	this->process(currentTick);
	this->render();
	lastTick = currentTick;
}

void GamePage::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_SPACE) {
		ctx->router->changePage(PageKeys::endingPage);
	}
}

void GamePage::process(Uint64 currentTick)
{
	const auto t = double(currentTick - lastTick) / 100;

	for (auto floor : floors) {
		floor->process(currentTick);
	}

	playerA = { 0, GAME_GRAVITY };
	playerV.y += playerA.y * t;
	playerV.y = std::min(playerV.y, GAME_PLAYER_MAX_V_Y);

	auto newPlayerY = playerPos.y + playerV.y * t;
	auto newPlayerX = playerPos.x;

	// ¹Ù´Ú ÆÇÁ¤
	bool isFloor = false;
	double floorAcc = 0;
	double floorY = 0;
	for (const auto floor : floors) {
		if (newPlayerY <= floor->posY && floor->posY <= newPlayerY + GAME_PLAYER_H) {
			for (const auto& line : floor->lines) {
				if (line.left <= newPlayerX + GAME_PLAYER_W && newPlayerX <= line.right) {
					isFloor = true;
					floorAcc = line.acceleration;
					floorY = floor->posY;
				}
			}
		}
	}

	if (isFloor) {
		newPlayerY = floorY - GAME_PLAYER_H;
	}

	playerPos.y = newPlayerY;
	playerPos.x = newPlayerX;

}

void GamePage::render()
{
	ctx->renderer->clear();

	auto backGroundImage = ctx->resources->images.get(ImageResources::background);
	ctx->renderer->drawImage(backGroundImage, 0, 0, backGroundImage->width, backGroundImage->height);

	CoordinateConverter converter(camera);

	auto screenPlayer = converter.convert(playerPos);
	auto playerImage = ctx->resources->images.get(ImageResources::player);
	ctx->renderer->drawImage(playerImage, screenPlayer.x, screenPlayer.y, playerImage->width, playerImage->height);

	
	//auto stopBlock1 = ctx->resources->images.get(ImageResources::stopBlock1);
	//ctx->renderer->drawImage(stopBlock1, 200, 200, stopBlock1->width, stopBlock1->height);


	for (auto floor : floors) {
		floor->render(ctx->renderer);
	}

	ctx->renderer->render();
}
