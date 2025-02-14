#include <iostream>
#include "const.h"
#include "GamePage.h"
#include "CoordinateConverter.h"
#include "DownFloorFactory.h"

long long highScore = 0;

GamePage::GamePage(const GameContext* ctx) : 
	ctx(ctx),
	lastTick(0),
	playerDirection(0),
	isGameOver(false),
	score(0)
{
}

GamePage::~GamePage()
{
}

void GamePage::init()
{
	ctx->resources->musics.get(MusicResources::background)->play();
	ctx->resources->sounds.get(SoundResources::click)->play();

	score = 0;
	lastTick = 0;
	isGameOver = false;

	playerPos = Point<double>(100, 300);
	playerV = Point<double>(0, 0);
	playerA = Point<double>(0, 0);

	camera = { 0,0 };

	playerDirection = 0;

	floors.clear();

	{
		auto floor = DownFloorFactory::create();
		floor->posY = camera.y + GAME_SCREEN_HEIGHT - GAME_FLOOR_GAP;
		floor->init();
		floors.push_back(floor);
	}

	{
		auto floor = DownFloorFactory::create();
		floor->posY = camera.y + GAME_SCREEN_HEIGHT;
		floor->init();
		floors.push_back(floor);
	}
}

void GamePage::tick(Uint64 currentTick)
{
	if (lastTick == 0) {
		lastTick = currentTick;
		return;
	}
	
	if (!isGameOver) {
		this->process(currentTick);
	}
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

void GamePage::onMouseLeftDown(int x, int y)
{
	if (isGameOver) {
		if (117 <= x && x <= 260 && 468 <= y && y <= 514) {
			ctx->router->changePage(PageKeys::introPage);
		}
		if (350 <= x && x <= 495 && 468 <= y && y <= 514) {
			this->init();
		}
	}
}

void GamePage::process(Uint64 currentTick)
{
	const auto t = double(currentTick - lastTick) / 100;
	
	if (playerPos.y - camera.y >= GAME_CAMERA_FULL_SPEED_LINE) {
		camera.y += GAME_PLAYER_MAX_V_Y * t;
	}
	else if (playerPos.y - camera.y >= GAME_CAMERA_HALF_SPEED_LINE) {
		camera.y += (GAME_PLAYER_MAX_V_Y - GAME_SCROLL_SPEED) / 2 * t;
	}
	else {
		camera.y += GAME_SCROLL_SPEED * t;
	}
	

	// 발판 추가
	if (floors.empty() || floors.back()->posY - camera.y < GAME_SCREEN_HEIGHT) {
		auto floor = DownFloorFactory::create();
		floor->posY = camera.y + GAME_SCREEN_HEIGHT + GAME_FLOOR_GAP;
		floor->init();
		floors.push_back(floor);
	}

	if (!floors.empty() && floors.front()->posY - camera.y < -100) {
		delete floors.front();
		floors.pop_front();
	}

	for (auto floor : floors) {
		floor->process(currentTick);
	}

	playerA = { 0, GAME_GRAVITY };
	playerV.y += playerA.y * t;
	playerV.y = std::min(playerV.y, GAME_PLAYER_MAX_V_Y);

	playerV.x = playerDirection * GAME_PLAYER_SPEED * t;

	auto newPlayerY = playerPos.y + playerV.y * t;
	auto newPlayerX = playerPos.x + playerV.x * t;

	// 바닥 판정
	bool isFloor;
	double floorAcc, floorY;
	std::tie(isFloor, floorAcc, floorY) = this->floorCheck(newPlayerX, newPlayerY, playerPos.y);

	if (isFloor) {
		newPlayerY = floorY - GAME_PLAYER_H;
		playerV.y = 0;
	}

	// 스코어 계산
	score = std::max((long long)(playerPos.y) / 100 - 6, 0ll);

	// 사망 판정
	if (newPlayerY < camera.y) {
		ctx->resources->sounds.get(SoundResources::gameover)->play();
		ctx->resources->musics.get(MusicResources::background)->stop();
		
		highScore = std::max(highScore, score);
		
		isGameOver = true;
		return;
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

	CoordinateConverter converter(camera);
	{
		auto backGroundImage = ctx->resources->images.get(ImageResources::background);
		int delta = int(camera.y) % backGroundImage->height;
		ctx->renderer->drawImage(backGroundImage, 0, -delta, backGroundImage->width, backGroundImage->height);
		ctx->renderer->drawImage(backGroundImage, 0, -delta + backGroundImage->height, backGroundImage->width, backGroundImage->height);
	}


	auto screenPlayer = converter.convert(playerPos);
	auto playerImage = ctx->resources->images.get(ImageResources::player);
	ctx->renderer->drawImage(playerImage, screenPlayer.x, screenPlayer.y, playerImage->width, playerImage->height);

	if (playerPos.x >= GAME_SCREEN_WIDTH - GAME_PLAYER_W) {
		auto screenPlayer = converter.convert({-(GAME_SCREEN_WIDTH - playerPos.x), playerPos.y});
		ctx->renderer->drawImage(playerImage, screenPlayer.x, screenPlayer.y, playerImage->width, playerImage->height);
	}
	

	for (auto floor : floors) {
		floor->render(ctx, &converter);
	}

	{
		auto font = ctx->resources->fonts.get(FontResources::uiFont);
		std::string str = "Score: ";
		str += std::to_string(score);
		ctx->renderer->drawText(font, str, 10, 10, { 255,255,255 });
		
	}


	if (isGameOver) {
		auto image = ctx->resources->images.get(ImageResources::gameoverModal);
		ctx->renderer->drawImage(image, 50, 250, image->width, image->height);

		auto font = ctx->resources->fonts.get(FontResources::scoreFont);
		std::string sstr = "Score: ";
		sstr += std::to_string(score);
		ctx->renderer->drawText(font, sstr, 110, 380, { 0,0,0 });

		std::string hsstr = "High Score: ";
		hsstr += std::to_string(highScore);
		ctx->renderer->drawText(font, hsstr, 300, 380, { 0,0,0 });
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
