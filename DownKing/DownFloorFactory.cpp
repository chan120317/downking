#include "DownFloorFactory.h"
#include "DownFloorStatic.h"
#include "DownFloorMoveLeft.h"
#include "DownFloorMoveRight.h"
#include "random.h"

DownFloorBase* DownFloorFactory::create()
{
	int rnum = randInt(0, 2);

	if (rnum == 0)
		return new DownFloorStatic();
	else if (rnum == 1)
		return new DownFloorMoveLeft();
	else if (rnum == 2)
		return new DownFloorMoveRight();
}
