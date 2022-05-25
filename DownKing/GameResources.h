#pragma once
#include "ResourceCollection.h"
#include "GameFont.h"
#include "GameImage.h"
#include "GameMusic.h"
#include "GameSound.h"
#include "common.h"

class GameResources
{
public:
	ResourceCollection<FontResources, GameFont*> fonts;
	ResourceCollection<ImageResources, GameImage*> images;
	ResourceCollection<MusicResources, GameMusic*> musics;
	ResourceCollection<SoundResources, GameSound*> sounds;
};

