#pragma once


template <typename T>
class Point {
public:
	T x;
	T y;

	Point() {
		x = 0; y = 0;
	}

	Point(T x, T y) {
		this->x = x;
		this->y = y;
	}
};

