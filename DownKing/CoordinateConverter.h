#pragma once
#include "util.h"

class CoordinateConverter {
public:
	CoordinateConverter(Point<double> base);

	Point<double> convert(Point<double> point);
	double convertY(double value);

private:
	Point<double> base;
};
