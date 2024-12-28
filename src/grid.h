#pragma once

#include <vector>
#include "raylib.h"

class Grid
{
public:
	Grid();
	void Init();
	void Print() const;
	void Draw() const;
	int grid[20][10];
	bool IsOutOfBounds(int row, int col) const;

	void SetCell(int row, int col, int value);
	bool IsCellEmpty(int row, int col) const;

	int ClearFullRows();

private:
	void ClearRow(int row);
	bool IsRowFull(int row) const;
	void MoveRowDown(int row, int numRows);
	int numRows, numCols;
	int cellSize;
	std::vector<Color> colors;
};