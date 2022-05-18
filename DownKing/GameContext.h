#pragma once
#include "PageRouter.h"
#include "GameRenderer.h"
#include "GameResources.h"

class GameContext
{
public:
	PageRouter* router;
	GameRenderer* renderer;
	GameResources* resources;
};

