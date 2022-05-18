#include "GamePage.h"
#include "CoordinateConverter.h"
#include <iostream>


constexpr double GAME_GRAVITY = 3.0;
constexpr double GAME_PLAYER_MAX_VY = 60.0;

GamePage::GamePage(const GameContext* ctx) : 
	ctx(ctx)
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
}

void GamePage::tick(Uint64 currentTick)
{
	this->process(currentTick);
	this->render();
}

void GamePage::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_SPACE) {
		ctx->router->changePage(PageKeys::endingPage);
	}
}

void GamePage::process(Uint64 currentTick)
{
	const auto t = double(currentTick) / 10000;

	playerA = { 0, GAME_GRAVITY };

	playerV.y += playerA.y * t;

	playerV.y = std::min(playerV.y, GAME_PLAYER_MAX_VY);

	playerPos.y += playerV.y * t;

}

void GamePage::render()
{
	ctx->renderer->clear();

	CoordinateConverter converter(camera);

	auto screenPlayer = converter.convert(playerPos);
	auto playerImage = ctx->resources->images.get(ImageResources::player);
	ctx->renderer->drawImage(playerImage, screenPlayer.x, screenPlayer.y, playerImage->width, playerImage->height);

	ctx->renderer->render();
}
