#include "DownFloorFactory.h"
#include "DownFloorStatic.h"
#include "DownFloorMoveLeft.h"
#include "DownFloorMoveRight.h"
#include "DownFloorBlink.h"
#include "random.h"

DownFloorBase* DownFloorFactory::create()
{
	int rnum = randInt(0, 3);

	if (rnum == 0)
		return new DownFloorStatic();
	else if (rnum == 1)
		return new DownFloorMoveLeft();
	else if (rnum == 2)
		return new DownFloorMoveRight();
	else if (rnum == 3)
		return new DownFloorBlink();
}
