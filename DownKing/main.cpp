#include "SDL.h"
#include "SDL_ttf.h"
#include "PageRouter.h"
#include "GamePage.h"
#include "EndingPage.h"
#include "IntroPage.h"
#include "EventHandler.h"

GameResources* loadGameResources();

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow("Middle Test", 100, 100, 1280, 720, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	PageRouter* router = new PageRouter();
	GameRenderer* gameRenderer = new GameRenderer(renderer);

	GameContext* gameContext = new GameContext();
	gameContext->router = router;
	gameContext->renderer = gameRenderer;
	gameContext->resources = loadGameResources();

	router->use(PageKeys::introPage, new IntroPage(gameContext));
	router->use(PageKeys::gamePage, new GamePage(gameContext));
	router->use(PageKeys::endingPage, new EndingPage(gameContext));

	router->init(PageKeys::introPage);

	auto lastTick = SDL_GetTicks64();
	while (true) {
		auto currentPage = router->getCurrent();

		auto sp = EventHandler::triggerEvents(currentPage);
		if (sp == SpecialEvents::exit) {
			break;
		}

		auto currentTick = SDL_GetTicks64();
		auto elapsed = currentTick - lastTick;
		if (elapsed < 10) {
			continue;
		}
		lastTick = currentTick;
		currentPage->tick(currentTick);

	};

	delete gameContext;

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	return 0;
}


GameResources* loadGameResources()
{
	GameResources* res = new GameResources();

	return res;
}
