#include "GameSound.h"
#include <iostream>

GameSound::GameSound(const char* path)
{
	this->chunk = Mix_LoadWAV(path);
	if (!this->chunk) {
		std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
		throw "Failed to load music";
	}

}

GameSound::~GameSound()
{
	Mix_FreeChunk(this->chunk);
}

void GameSound::play()
{
	Mix_PlayChannel(-1, this->chunk, 0);
}
