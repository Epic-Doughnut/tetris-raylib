#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game
{
public:
	Game();
	~Game();
	void Draw() const;
	void Update();

	void MoveBlockDown();

	bool IsGameOver() const;
	void ChangeScore(int value);
	int GetScore() const;

private:
	std::vector<Block> blocks;
	Block currentBlock, nextBlock;
	Grid grid;
	int score;
	bool gameOver;

	Music music;
	Sound clearSound, lockSound, rotateSound, gameOverSound;

	void HandleInput();
	void UpdateMusic();

	Block GetRandomBlock();
	std::vector<Block> GetBlocks() const;

	bool IsBlockOutOfBounds() const;
	void LockBlock();
	void GameOver();
	bool BlockFits() const;

	void MoveBlockRight();
	void MoveBlockLeft();
	void RotateBlock();

	bool CanMove() const;
};