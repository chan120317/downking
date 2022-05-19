#include "DownFloorFactory.h"
#include "DownFloorStatic.h"

DownFloorBase* DownFloorFactory::create()
{
	return new DownFloorStatic();
}
