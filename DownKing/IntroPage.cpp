#include "IntroPage.h"
#include "common.h"

IntroPage::IntroPage(const GameContext* ctx) : ctx(ctx)
{
}

IntroPage::~IntroPage()
{
}

void IntroPage::init()
{
	ctx->resources->musics.get(MusicResources::menu)->play();
	ctx->resources->sounds.get(SoundResources::start)->play();
}

void IntroPage::tick(Uint64 currentTick)
{
	ctx->renderer->setBackground({ 222,222,222 });
	ctx->renderer->clear();


	auto backGroundImage = ctx->resources->images.get(ImageResources::introImage);
	ctx->renderer->drawImage(backGroundImage, 0, 0, backGroundImage->width, backGroundImage->height);


	ctx->renderer->render();
}

void IntroPage::onMouseLeftDown(int x, int y)
{
	if (x > 210 && y > 500 && x < 390 && y < 550) {
		ctx->router->changePage(PageKeys::gamePage);
	}
	if (x > 210 && y > 630 && x < 390 && y < 680) {
		
	}
}
