#include "PageRouter.h"

PageRouter::PageRouter()
{
	currentPage = nullptr;
}

PageRouter::~PageRouter()
{
	for (auto page : this->pages) {
		if (page != nullptr) {
			delete page;
		}
	}
}

void PageRouter::use(PageKeys key, IPage* page)
{
	auto idx = static_cast<int>(key);

	if (idx >= this->pages.size()) {
		this->pages.resize(idx + 1);
	}
	this->pages[idx] = page;
}

void PageRouter::init(PageKeys initPageKey)
{
	auto idx = static_cast<int>(initPageKey);
	this->currentPage = this->pages.at(idx);
	this->currentPage->init();
}

IPage* PageRouter::getCurrent()
{
	return this->currentPage;
}

void PageRouter::changePage(PageKeys pageKey)
{
	this->currentPage->fini();
	auto idx = static_cast<int>(pageKey);
	this->currentPage = this->pages.at(idx);
	this->currentPage->init();
}
