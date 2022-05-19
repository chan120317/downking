#include <iostream>
#include "GamePage.h"
#include "CoordinateConverter.h"
#include "DownFloorStatic.h"

constexpr double GAME_GRAVITY = 5.0;
constexpr double GAME_PLAYER_MAX_V_Y = 40.0;
constexpr double GAME_PLAYER_SPEED = 200.0;

constexpr double GAME_PLAYER_W = 32.0;
constexpr double GAME_PLAYER_H = 32.0;

GamePage::GamePage(const GameContext* ctx) : 
	ctx(ctx),
	lastTick(0),
	playerDirection(0)
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

	playerDirection = 0;

	{
		auto floor = new DownFloorStatic();
		floor->posY = 200;
		floors.push_back(floor);
		floor->init();
	}
	
	{
		auto floor = new DownFloorStatic();
		floor->posY = 400;
		floors.push_back(floor);
		floor->init();
	}
	{
		auto floor = new DownFloorStatic();
		floor->posY = 600;
		floors.push_back(floor);
		floor->init();
	}


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
	if (keyCode == SDLK_LEFT) {
		playerDirection = -1;
	}
	else if (keyCode == SDLK_RIGHT) {
		playerDirection = 1;
	}

	if (keyCode == SDLK_SPACE) {
		ctx->router->changePage(PageKeys::endingPage);
	}
}

void GamePage::onKeyUp(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_LEFT) {
		if (playerDirection == -1) {
			playerDirection = 0;
		}
	}
	else if (keyCode == SDLK_RIGHT) {
		if (playerDirection == 1) {
			playerDirection = 0;
		}
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

	playerV.x = playerDirection * GAME_PLAYER_SPEED * t;

	auto newPlayerY = playerPos.y + playerV.y * t;
	auto newPlayerX = playerPos.x + playerV.x * t;

	// ¹Ù´Ú ÆÇÁ¤
	bool isFloor;
	double floorAcc, floorY;
	std::tie(isFloor, floorAcc, floorY) = this->floorCheck(newPlayerX, newPlayerY, playerPos.y);

	if (isFloor) {
		newPlayerY = floorY - GAME_PLAYER_H;
		playerV.y = 0;
	}

	playerPos.y = newPlayerY;
	if (newPlayerX < 0) {
		playerPos.x = GAME_SCREEN_WIDTH - 1.0;
	}
	else if (newPlayerX >= GAME_SCREEN_WIDTH - 1.0) {
		playerPos.x = 0;
	}
	else {
		playerPos.x = newPlayerX;
	}

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

	if (playerPos.x >= GAME_SCREEN_WIDTH - GAME_PLAYER_W) {
		auto screenPlayer = converter.convert({-(GAME_SCREEN_WIDTH - playerPos.x), playerPos.y});
		ctx->renderer->drawImage(playerImage, screenPlayer.x, screenPlayer.y, playerImage->width, playerImage->height);
	}
	
	//auto stopBlock1 = ctx->resources->images.get(ImageResources::stopBlock1);
	//ctx->renderer->drawImage(stopBlock1, 200, 200, stopBlock1->width, stopBlock1->height);


	for (auto floor : floors) {
		floor->render(ctx->renderer);
	}

	ctx->renderer->render();
}

std::tuple<bool, double, double> GamePage::floorCheck(double newPlayerX, double newPlayerY, double lastPlayerY)
{
	bool isFloor = false;
	double floorAcc = 0;
	double floorY = 0;
	for (const auto floor : floors) {
		if (floor->posY < lastPlayerY + GAME_PLAYER_H - 3.0) {
			continue;
		}
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
	return { isFloor, floorAcc, floorY };
}
