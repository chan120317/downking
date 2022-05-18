#include "IntroPage.h"


IntroPage::IntroPage(const GameContext* ctx) : ctx(ctx)
{
}

IntroPage::~IntroPage()
{
}

void IntroPage::init()
{
}

void IntroPage::tick(Uint64 currentTick)
{
	ctx->renderer->setBackground({ 222,222,222 });
	ctx->renderer->clear();

	ctx->renderer->render();
}

void IntroPage::onMouseLeftDown(int x, int y)
{
	ctx->router->changePage(PageKeys::gamePage);
}
