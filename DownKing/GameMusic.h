#pragma once
#include "SDL_mixer.h"

class GameMusic
{
public:
	GameMusic(const char* path);
	~GameMusic();

	void play();
	void stop();

private:
	Mix_Music* music;
};

