#include <iostream>
#include "grid.h"
#include "colors.h"

Grid::Grid()
{
	numRows = 20;
	numCols = 10;
	cellSize = 30;

	Init();

	colors = GetCellColors();
}

void Grid::Init()
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			grid[i][j] = 0;
		}
	}
}

void Grid::Print() const
{
	for (int i = 0; i < numRows; ++i)
	{
		for (int j = 0; j < numCols; ++j)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

#define MARGIN 1

void Grid::Draw() const
{
	for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{
			const int cellValue = grid[i][j];
			DrawRectangle(j * cellSize + MARGIN + 10, i * cellSize + MARGIN + 10, cellSize - MARGIN, cellSize - MARGIN, colors[cellValue]);
		}
	}
}

bool Grid::IsOutOfBounds(int row, int col) const
{
	return row < 0 or row >= numRows or
		   col < 0 or col >= numCols;
}

void Grid::SetCell(int row, int col, int value)
{
	grid[row][col] = value;
}

bool Grid::IsCellEmpty(int row, int col) const
{
	return grid[row][col] == 0;
}

int Grid::ClearFullRows()
{
	int rowsCleared = 0;
	for (int row = numRows; row--;)
	{
		// If a row is full, clear it. Otherwise, move it down.
		if (IsRowFull(row))
		{
			++rowsCleared;
			ClearRow(row);
		}
		else if (rowsCleared > 0)
		{
			MoveRowDown(row, rowsCleared);
		}
	}
	return rowsCleared;
}

void Grid::ClearRow(int row)
{
	for (int col = 0; col < numCols; ++col)
	{
		grid[row][col] = 0;
	}
}

bool Grid::IsRowFull(int row) const
{
	for (int col = 0; col < numCols; ++col)
	{
		if (IsCellEmpty(row, col))
		{
			return false;
		}
	}
	return true;
}

void Grid::MoveRowDown(int row, int numRows)
{
	for (int col = 0; col < numCols; ++col)
	{
		grid[row + numRows][col] = grid[row][col];
	}

	ClearRow(row);
}