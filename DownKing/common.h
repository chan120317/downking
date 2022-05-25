#pragma once

constexpr int GAME_SCREEN_WIDTH = 600;
constexpr int GAME_SCREEN_HEIGHT = 800;

enum class PageKeys {
	introPage,
	gamePage,
	endingPage
};

enum class FontResources {
	uiFont,
	resultFont,
};

enum class ImageResources {
	player,
	background,
	introImage,
	stopBlock1,
	stopBlock2, 
	stopBlockleft,
	stopBlockright,
	rightBlock1,
	rightBlock2,
	rightBlockleft,
	rightBlockright, 
	leftBlock1,
	leftBlock2,
	leftBlockleft,
	leftBlockright,
	blinkBlock1,
	blinkBlock2,
	blinkBlockleft,
	blinkBlockright,
};

enum class MusicResources {
	background,
	menu,
};

enum class SoundResources {
	opening,
	click,
	gameover,

};
