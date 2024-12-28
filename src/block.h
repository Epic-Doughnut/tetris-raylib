#pragma once

#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
	Block();
	void Draw(int offsetX, int offsetY) const;
	int id;
	std::map<int, std::vector<Position>> cells;

	void RotateLeft();
	void RotateRight();

	void Move(int columns, int rows);

	std::vector<Position> GetCellPositions() const;

private:
	int colOffset, rowOffset;
	int cellSize;
	unsigned short rotationState;
	std::vector<Color> colors;
};