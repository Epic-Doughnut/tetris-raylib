#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <string>

double lastUpdateTime = 0;
const double GAME_SPEED = 0.2;

bool EventTriggered(double interval)
{
	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval)
	{
		lastUpdateTime = currentTime;
		return true;
	}

	return false;
}

int main()
{
	InitWindow(500, 620, "Tetris Game");
	SetTargetFPS(60);

	// Font font = LoadFontEx("fonts/BRLNSB.ttf", 24, 0, 0);
	Font font = GetFontDefault();

	Game game = Game();

	while (!WindowShouldClose())
	{
		game.Update();

		// Move the block down every 0.2 seconds
		if (not game.IsGameOver() and EventTriggered(GAME_SPEED))
			game.MoveBlockDown();

		BeginDrawing();
		ClearBackground(darkBlue);

		// UI
		// Score
		DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
		DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

		const char *scoreText = std::to_string(game.GetScore()).c_str();
		const Vector2 textSize = MeasureTextEx(font, scoreText, 34, 2);
		const int textWidth = textSize.x;

		DrawTextEx(font, scoreText, {(float)320 + (170 - textWidth) / 2, 65}, 34, 2, WHITE);

		// Next block
		DrawTextEx(font, "Next", {375, 175}, 38, 2, WHITE);
		DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

		if (game.IsGameOver())
			DrawTextEx(font, "Game Over", {320, 450}, 38, 2, RED);

		game.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}