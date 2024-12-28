#include "game.h"
#include <random>

Game::Game()
{
	grid = Grid();
	blocks = GetBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;

	InitAudioDevice();

	// Load music
	music = LoadMusicStream("audio/music.mp3");
	PlayMusicStream(music);

	// Load sounds
	clearSound = LoadSound("audio/clear.wav");
	lockSound = LoadSound("audio/lock.wav");
	rotateSound = LoadSound("audio/rotate.wav");
	gameOverSound = LoadSound("audio/gameover.wav");
}

Game::~Game()
{
	UnloadSound(clearSound);
	UnloadSound(lockSound);
	UnloadSound(rotateSound);
	UnloadSound(gameOverSound);

	UnloadMusicStream(music);
	CloseAudioDevice();
}

/**
 * Cycle through every block before repeating with a random permutation
 */
Block Game::GetRandomBlock()
{
	if (blocks.empty())
	{
		blocks = GetBlocks();
	}
	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);

	return block;
}

std::vector<Block> Game::GetBlocks() const
{
	return {LBlock(),
			JBlock(),
			IBlock(),
			OBlock(),
			SBlock(),
			TBlock(),
			ZBlock()};
	;
}

#define MARGIN 1
#define OFFSET 10

void Game::Draw() const
{
	grid.Draw();

	const int offsetX = MARGIN + OFFSET;
	const int offsetY = MARGIN + OFFSET;
	currentBlock.Draw(offsetX, offsetY);
	switch (nextBlock.id)
	{
	case 1: // L block
		nextBlock.Draw(270, 270);
		break;
	case 3: // I block
		nextBlock.Draw(230, 290);
		break;
	case 4: // O block
		nextBlock.Draw(250, 280);
		break;
	default:
		nextBlock.Draw(255, 270);
	}
}

void Game::Update()
{
	UpdateMusic();
	HandleInput();
}

void Game::HandleInput()
{
	int keyPressed = GetKeyPressed();

	// Restart the game on any button when gameover
	if (IsGameOver() and keyPressed)
	{
		*this = Game();
		return;
	}

	switch (keyPressed)
	{
	case KEY_LEFT:
	case KEY_A:
		MoveBlockLeft();
		break;
	case KEY_RIGHT:
	case KEY_D:
		MoveBlockRight();
		break;
	case KEY_DOWN:
	case KEY_S:
		MoveBlockDown();
		// Award some points for being faster
		ChangeScore(1);
		break;
	case KEY_UP:
	case KEY_W:
		RotateBlock();
		break;
	};
}

void Game::UpdateMusic()
{
	UpdateMusicStream(music);
}

bool Game::IsBlockOutOfBounds() const
{
	auto tiles = currentBlock.GetCellPositions();
	for (Position pos : tiles)
	{
		if (grid.IsOutOfBounds(pos.row, pos.column))
		{
			return true;
		}
	}
	return false;
}

void Game::LockBlock()
{
	auto tiles = currentBlock.GetCellPositions();
	for (Position pos : tiles)
	{
		grid.SetCell(pos.row, pos.column, currentBlock.id);
	}
	currentBlock = nextBlock;

	if (not BlockFits())
	{
		GameOver();
	}

	nextBlock = GetRandomBlock();

	int rowsCleared = grid.ClearFullRows();
	/**
	 * Score calculation:
	 * 1 row: 100
	 * 2 rows: 300
	 * 3 rows: 500
	 * 4 rows: 1000	 *
	 */
	switch (rowsCleared)
	{
	case 4:
		ChangeScore(500);
	case 3:
		ChangeScore(200);
	case 2:
		ChangeScore(200);
	case 1:
		ChangeScore(100);
		PlaySound(clearSound);
		break;
	case 0:
		break;
	}

	PlaySound(lockSound);
}

void Game::GameOver()
{
	gameOver = true;
	PlaySound(gameOverSound);
}

/**
 * Check if the current block fits in the grid (all unoccupied)
 */
bool Game::BlockFits() const
{
	auto tiles = currentBlock.GetCellPositions();
	for (Position pos : tiles)
	{
		if (not grid.IsCellEmpty(pos.row, pos.column))
		{
			return false;
		}
	}

	return true;
}

void Game::MoveBlockDown()
{
	currentBlock.Move(0, 1);
	if (not CanMove())
	{
		currentBlock.Move(0, -1);
		LockBlock();
	}
}

bool Game::IsGameOver() const
{
	return gameOver;
}

void Game::ChangeScore(int value)
{
	score += value;
}

int Game::GetScore() const
{
	return score;
}

void Game::MoveBlockRight()
{
	currentBlock.Move(1, 0);
	if (not CanMove())
	{
		currentBlock.Move(-1, 0);
	}
}

void Game::MoveBlockLeft()
{
	currentBlock.Move(-1, 0);
	if (not CanMove())
	{
		currentBlock.Move(1, 0);
	}
}

void Game::RotateBlock()
{
	currentBlock.RotateRight();
	if (not CanMove())
	{
		currentBlock.RotateLeft();
		return;
	}

	PlaySound(rotateSound);
}

bool Game::CanMove() const
{
	return not IsBlockOutOfBounds() and BlockFits();
}
