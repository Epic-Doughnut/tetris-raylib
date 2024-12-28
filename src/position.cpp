#include "position.h"

Position::Position(int row, int column)
{
	this->row = row;
	this->column = column;
}

/**
 * @param size The size of the vector
 * @param values The vector of values, stored as binary numbers representing each row
 */
std::vector<Position> Position::FromVector(const int size, const std::vector<int> values)
{
	std::vector<Position> ans;
	for (int i = 0; i < size; ++i)
	{
		for (int j = size; j--;)
		{
			if (values[i] & (1 << j))
			{
				ans.push_back(Position(i, size - j));
			}
		}
	}
	return ans;
}
