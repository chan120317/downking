#pragma once
#include <random>


int randInt(int a, int b) {
	std::random_device rd;
	auto gen = std::mt19937(rd());

	std::uniform_int_distribution<int> dis(a, b);
	return dis(gen);
};

double randDouble(double a, double b) {
	std::random_device rd;
	auto gen = std::mt19937(rd());

	std::uniform_real_distribution<double> dis(a, b);
	return dis(gen);
};