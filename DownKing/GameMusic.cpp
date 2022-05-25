#include "GameMusic.h"
#include <iostream>

GameMusic::GameMusic(const char* path)
{
	auto music = Mix_LoadMUS(path);
	if (!music) {
		std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
		throw "Failed to load music";
	}
	this->music = music;
}

GameMusic::~GameMusic()
{
	Mix_FreeMusic(this->music);
}

void GameMusic::play()
{
	Mix_PlayMusic(this->music, -1);
}

void GameMusic::stop()
{

}
