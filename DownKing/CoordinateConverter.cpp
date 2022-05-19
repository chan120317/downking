#include "CoordinateConverter.h"

CoordinateConverter::CoordinateConverter(Point<double> base): base(base)
{
}

Point<double> CoordinateConverter::convert(Point<double> point)
{
	return Point<double>(point.x - base.x, point.y - base.y);
}

double CoordinateConverter::convertY(double value)
{
	return value - base.y;
}
