#include "GamePage.h"

GamePage::GamePage(const GameContext* ctx) : ctx(ctx)
{
}

GamePage::~GamePage()
{
}

void GamePage::init()
{
}

void GamePage::tick(Uint64 currentTick)
{
	ctx->renderer->clear();


	ctx->renderer->render();
}

void GamePage::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_SPACE) {
		ctx->router->changePage(PageKeys::endingPage);
	}
}
