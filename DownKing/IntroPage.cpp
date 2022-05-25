#include "IntroPage.h"


IntroPage::IntroPage(const GameContext* ctx) : ctx(ctx)
{
}

IntroPage::~IntroPage()
{
}

void IntroPage::init()
{
	ctx->resources->musics.get(MusicResources::menu)->play();
}

void IntroPage::tick(Uint64 currentTick)
{
	ctx->renderer->setBackground({ 222,222,222 });
	ctx->renderer->clear();

	ctx->renderer->drawText(ctx->resources->fonts.get(FontResources::uiFont), "Click anywhere to start.", 10, 10, { 0,0,0 });

	ctx->renderer->render();
}

void IntroPage::onMouseLeftDown(int x, int y)
{
	ctx->router->changePage(PageKeys::gamePage);
}
