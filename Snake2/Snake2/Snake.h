#pragma once

/* Snake class. Contains:
   - information about snake size and position
   - methods to move snake
*/

#include <string>
#include "Constants.h"

class Snake {
public:
	Snake();
	~Snake() {}

	// Move snake by 1 step in specified direction. 
	void MakeStep();
	
	// Direction of snake movement
	Direction GetCurrentDirection() const { return direction; }
	void SetCurrentDirection(const Direction& newDirection) { direction = newDirection; }
	// Length of snake
	int GetLength() const { return length; }
	// Coordinates of snake part (position is from 0 to snake's length)
	int GetX(int position) const { return coords[position].x; }
	int GetY(int position) const { return coords[position].y; }
	// Path for picture of snake
	std::string GetSnakeTexturePath() const { return snakeTexturePath; }

	// do not copy or move Snake
	Snake(const Snake& other) = delete;
	Snake& operator= (const Snake& other) = delete;
	Snake& operator= (Snake&& other) = delete;

private:
	// Color of Snake
	const std::string snakeTexturePath = "images/snake2.png";
	int length;
	Direction direction;
	struct Coord { int x; int y; } coords[SNAKE_LENGTH_MAX];

	// proceed snake by 1 step on specified coordinate (x or y)
	void goAhead(int& coord, const int& maxCoordLength);
	void goBack(int& coord, const int& maxCoordLength);
};
