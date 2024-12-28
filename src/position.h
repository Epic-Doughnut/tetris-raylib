#pragma once
#include <vector>

class Position
{
public:
	Position(int row, int column);
	static std::vector<Position> FromVector(const int size, const std::vector<int> values);
	int row;
	int column;
};