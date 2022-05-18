#include "EventHandler.h"
#include "SDL.h"


SpecialEvents EventHandler::triggerEvents(IPage* page)
{
	SDL_Event evt;

	while (SDL_PollEvent(&evt)) {
		if (evt.type == SDL_QUIT) {
			return SpecialEvents::exit;
		}

		if (evt.type == SDL_KEYDOWN) {
			auto key = evt.key.keysym.sym;
			page->onKeyDown(key);
		}
		else if (evt.type == SDL_KEYUP) {
			auto key = evt.key.keysym.sym;
			page->onKeyUp(key);
		}
		else if (evt.type == SDL_MOUSEBUTTONDOWN) {
			if (evt.button.button == SDL_BUTTON_LEFT) {
				page->onMouseLeftDown(evt.button.x, evt.button.y);
			}
			else if (evt.button.button == SDL_BUTTON_RIGHT) {
				page->onMouseRightDown(evt.button.x, evt.button.y);
			}
		}
	}

	return SpecialEvents::proceed;
}
