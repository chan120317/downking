#pragma once
#include "util.h"

class CoordinateConverter {
public:
	CoordinateConverter(Point<double> base);

	Point<double> convert(Point<double> point);

private:
	Point<double> base;
};
