#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "PageRouter.h"
#include "GamePage.h"
#include "EndingPage.h"
#include "IntroPage.h"
#include "EventHandler.h"
#include "util.h"
#include <iostream>
GameResources* loadGameResources();

int main(int argc, char** argv) {
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
	Mix_VolumeMusic(10);
	Mix_Volume(-1, 10);
	TTF_Init();
	SDL_Window* window = SDL_CreateWindow("Middle Test", 100, 100, 600, 800, 0);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	std::cout << "SDL2 loaded." << std::endl;

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

	std::cout << "Everything loaded." << std::endl;

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
	Mix_CloseAudio();
	return 0;
}


GameResources* loadGameResources()
{
	GameResources* res = new GameResources();

	res->fonts.set(FontResources::uiFont, new GameFont("res/font/SBagroB.ttf", 25));
	res->fonts.set(FontResources::resultFont, new GameFont("res/font/SEBANG Gothic Bold.ttf",16));

	res->images.set(ImageResources::player, new GameImage("res/image/player.png", 32, 32));
	res->images.set(ImageResources::background, new GameImage("res/image/background.png", 600, 1600));
	res->images.set(ImageResources::introImage, new GameImage("res/image/intro_background.png", 600, 800));
	
	res->images.set(ImageResources::stopBlock1, new GameImage("res/image/s1.png", 36, 44));
	res->images.set(ImageResources::stopBlock2, new GameImage("res/image/s2.png", 64, 32));
	res->images.set(ImageResources::stopBlockleft, new GameImage("res/image/s1lmac.png", 40, 44));
	res->images.set(ImageResources::stopBlockright, new GameImage("res/image/s1rmac.png", 40, 44));

	res->images.set(ImageResources::rightBlock1, new GameImage("res/image/rm1.png", 36, 44));
	res->images.set(ImageResources::rightBlock2, new GameImage("res/image/rm2.png", 64, 32));
	res->images.set(ImageResources::rightBlockleft, new GameImage("res/image/rm1lmac.png", 40, 44));
	res->images.set(ImageResources::rightBlockright, new GameImage("res/image/rm1rmac.png", 40, 44));

	res->images.set(ImageResources::leftBlock1, new GameImage("res/image/lm1.png", 36, 44));
	res->images.set(ImageResources::leftBlock2, new GameImage("res/image/lm2.png", 64, 32));
	res->images.set(ImageResources::leftBlockleft, new GameImage("res/image/lm1lmac.png", 40, 44));
	res->images.set(ImageResources::leftBlockright, new GameImage("res/image/lm1rmac.png", 40, 44));

	res->images.set(ImageResources::blinkBlock1, new GameImage("res/image/ggam1.png", 36, 44));
	res->images.set(ImageResources::blinkBlock2, new GameImage("res/image/ggam2.png", 64, 32));
	res->images.set(ImageResources::blinkBlockleft, new GameImage("res/image/ggam1lmac.png", 40, 44));
	res->images.set(ImageResources::blinkBlockright, new GameImage("res/image/ggam1rmac.png", 40, 44));

	res->musics.set(MusicResources::background, new GameMusic("res/music/background.mp3"));
	res->musics.set(MusicResources::menu, new GameMusic("res/music/menu.mp3"));

	res->sounds.set(SoundResources::click, new GameSound("res/sound/click.wav"));
	res->sounds.set(SoundResources::gameover, new GameSound("res/sound/gameover.wav"));
	res->sounds.set(SoundResources::start, new GameSound("res/sound/start.wav"));

	std::cout << "Resources loaded." << std::endl;

	return res;
}
