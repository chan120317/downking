#include "EndingPage.h"

EndingPage::EndingPage(const GameContext* ctx): ctx(ctx)
{
}

EndingPage::~EndingPage()
{
}

void EndingPage::init()
{
}

void EndingPage::tick(Uint64 currentTick)
{
	ctx->renderer->clear();

	ctx->renderer->render();
}

void EndingPage::onMouseLeftDown(int x, int y)
{
	ctx->router->changePage(PageKeys::introPage);
}
