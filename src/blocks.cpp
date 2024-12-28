#include "block.h"
#include "position.h"

class LBlock : public Block
{
public:
	LBlock()
	{
		id = 1;
		cells[0] = {Position(0, 2),
					Position(1, 0),
					Position(1, 1),
					Position(1, 2)};
		cells[1] = {Position(0, 1),
					Position(1, 1),
					Position(2, 1),
					Position(2, 2)};
		cells[2] = {Position(1, 0),
					Position(1, 1),
					Position(1, 2),
					Position(2, 0)};
		cells[3] = {Position(0, 0),
					Position(0, 1),
					Position(1, 1),
					Position(2, 1)};
	}
};

class JBlock : public Block
{
public:
	JBlock()
	{
		id = 2;
		cells[0] = Position::FromVector(3, {0b100,
											0b111,
											0b000});
		cells[1] = Position::FromVector(3, {0b011,
											0b010,
											0b010});
		cells[2] = Position::FromVector(3, {0b000,
											0b111,
											0b001});
		cells[3] = Position::FromVector(3, {0b010,
											0b010,
											0b110});
	}
};

class IBlock : public Block
{
public:
	IBlock()
	{
		id = 3;
		cells[0] = Position::FromVector(4, {0b0000,
											0b1111,
											0b0000,
											0b0000});
		cells[1] = Position::FromVector(4, {0b0010,
											0b0010,
											0b0010,
											0b0010});
		cells[2] = Position::FromVector(4, {0b0000,
											0b0000,
											0b1111,
											0b0000});
		cells[3] = Position::FromVector(4, {0b0100,
											0b0100,
											0b0100,
											0b0100});
		// move up a row to center the block
		Move(0, -1);
	}
};

class OBlock : public Block
{
public:
	OBlock()
	{
		id = 4;
		cells[0] = cells[1] = cells[2] = cells[3] = Position::FromVector(2, {0b11, 0b11});
	}
};

class SBlock : public Block
{
public:
	SBlock()
	{
		id = 5;
		cells[0] = Position::FromVector(3, {0b011,
											0b110,
											0b000});
		cells[1] = Position::FromVector(3, {0b010,
											0b011,
											0b001});
		cells[2] = Position::FromVector(3, {0b000,
											0b011,
											0b110});
		cells[3] = Position::FromVector(3, {0b100,
											0b110,
											0b010});
	}
};

class TBlock : public Block
{
public:
	TBlock()
	{
		id = 6;
		cells[0] = Position::FromVector(3, {0b010,
											0b111,
											0b000});
		cells[1] = Position::FromVector(3, {0b010,
											0b011,
											0b010});
		cells[2] = Position::FromVector(3, {0b000,
											0b111,
											0b010});
		cells[3] = Position::FromVector(3, {0b010,
											0b110,
											0b010});
	}
};

class ZBlock : public Block
{
public:
	ZBlock()
	{
		id = 7;
		cells[0] = Position::FromVector(3, {0b110,
											0b011,
											0b000});
		cells[1] = Position::FromVector(3, {0b001,
											0b011,
											0b010});
		cells[2] = Position::FromVector(3, {0b000,
											0b110,
											0b011});
		cells[3] = Position::FromVector(3, {0b010,
											0b110,
											0b100});
	}
};