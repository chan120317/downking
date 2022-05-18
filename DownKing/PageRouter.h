#pragma once
#include <vector>
#include "SDL.h"
#include "iPage.h"
#include "common.h"

enum class PageRouterStatus
{
	PROCEED,
	EXIT
};

class PageRouter
{
public:
	PageRouter();
	~PageRouter();

	void use(PageKeys key, IPage* page);

	void init(PageKeys initPageKey);
	IPage* getCurrent();

	void changePage(PageKeys pageKey);

private:
	std::vector<IPage*> pages;
	IPage* currentPage;
};

