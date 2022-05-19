#pragma once
#include "util.h"

class DownInfoFloor {
public:
	DownInfoFloor(): left(0), right(0), acceleration(0) {

	}

	DownInfoFloor(double left, double right, double acc):
		left(left),
		right(right),
		acceleration(acc)
	{

	}

	double left;
	double right;
	double acceleration;
};
