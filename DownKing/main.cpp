#include "SDL.h"
#include "SDL_ttf.h"
#include "PageRouter.h"
#include "GamePage.h"
#include "EndingPage.h"
#include "IntroPage.h"
#include "EventHandler.h"
#include "util.h"

GameResources* loadGameResources();

int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow("Middle Test", 100, 100, 600, 800, 0);
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

	res->fonts.set(FontResources::uiFont, new GameFont("res/font/SBagroB.ttf", 16));
	res->fonts.set(FontResources::resultFont, new GameFont("res/font/SEBANG Gothic Bold.ttf",16));

	res->images.set(ImageResources::player, new GameImage("res/image/player.png", 32, 32));
	res->images.set(ImageResources::background, new GameImage("res/image/background.png", 600, 1600));
	
	res->images.set(ImageResources::stopBlock1, new GameImage("res/image/s1.png", 32, 32));
	res->images.set(ImageResources::stopBlock2, new GameImage("res/image/s2.png", 64, 32));
	res->images.set(ImageResources::stopBlockleft, new GameImage("res/image/s1lmac.png", 32, 32));
	res->images.set(ImageResources::stopBlockright, new GameImage("res/image/s1rmac.png", 32, 32));

	res->images.set(ImageResources::rightBlock1, new GameImage("res/image/rm1.png", 32, 32));
	res->images.set(ImageResources::rightBlock2, new GameImage("res/image/rm2.png", 64, 32));
	res->images.set(ImageResources::rightBlockleft, new GameImage("res/image/rm1lmac.png", 32, 32));
	res->images.set(ImageResources::rightBlockright, new GameImage("res/image/rm1rmac.png", 32, 32));

	res->images.set(ImageResources::leftBlock1, new GameImage("res/image/lm1.png", 32, 32));
	res->images.set(ImageResources::leftBlock2, new GameImage("res/image/lm2.png", 64, 32));
	res->images.set(ImageResources::leftBlockleft, new GameImage("res/image/lm1lmac.png", 32, 32));
	res->images.set(ImageResources::leftBlockright, new GameImage("res/image/lm1rmac.png", 32, 32));

	res->images.set(ImageResources::blinkBlock1, new GameImage("res/image/ggam1.png", 32, 32));
	res->images.set(ImageResources::blinkBlock2, new GameImage("res/image/ggam2.png", 64, 32));
	res->images.set(ImageResources::blinkBlockleft, new GameImage("res/image/ggam1lmac.png", 32, 32));
	res->images.set(ImageResources::blinkBlockright, new GameImage("res/image/ggam1rmac.png", 32, 32));


	return res;
}
