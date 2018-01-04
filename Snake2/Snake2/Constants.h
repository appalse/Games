#pragma once
#include <string>

const int SNAKE_LENGTH_MIN = 4;
const int SNAKE_LENGTH_MAX = 30;

enum class Direction : int
{
	RIGHT,
	DOWN,
	LEFT,
	UP
};

// Maximum cells count by y:
const int H = 15;
// Maximum cells count by x:
const int W = 20;

// Cell Size in pixels
const int CellSize = 16;

// Total window height in pixels
const int Height = CellSize * H;
// Total window width in pixels
const int Width = CellSize * W;

// Color of cell
const std::string CellTexturePath = "images/sand.png";

// Timeout in milliseconds
const int TIMEOUT = 100;
