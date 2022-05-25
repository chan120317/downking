#pragma once
#include "SDL_mixer.h"

class GameSound {
public:
	GameSound(const char* path);
	~GameSound();

	void play();

private:
	Mix_Chunk* chunk;
};
