#pragma once
#include "IPage.h"

enum class SpecialEvents {
	proceed,
	exit
};

class EventHandler
{
public:
	static SpecialEvents triggerEvents(IPage* page);
};

