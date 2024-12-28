#include "block.h"
#include <stdexcept>
#include <iostream>

Block::Block()
{
	cellSize = 30;
	rotationState = 0;
	colors = GetCellColors();
	colOffset = 3; // center the new block
	rowOffset = 0;
}

#define MARGIN 1
void Block::Draw(int offsetX, int offsetY) const
{
	const std::vector<Position> tiles = GetCellPositions();
	for (Position tile : tiles)
	{
		DrawRectangle(tile.column * cellSize + offsetX, tile.row * cellSize + offsetY, cellSize - MARGIN, cellSize - MARGIN, colors[id]);
	}
}

void Block::RotateLeft()
{
	rotationState = (rotationState + 3) % cells.size();
}

void Block::RotateRight()
{
	rotationState = (rotationState + 1) % cells.size();
}

void Block::Move(int columns, int rows)
{
	rowOffset += rows;
	colOffset += columns;
}

std::vector<Position> Block::GetCellPositions() const
{
	// if (rotationState < 0 or rotationState >= cells.size())
	// {
	// 	throw std::out_of_range("Error: " + std::to_string(rotationState) +
	// 							" out of bounds [0-" + std::to_string(cells.size()) + "]\n");
	// }

	const std::vector<Position> tiles = cells.at(rotationState);

	std::vector<Position> positions;

	for (const Position &tile : tiles)
	{
		positions.push_back(Position(tile.row + rowOffset, tile.column + colOffset));
	}

	return positions;
}