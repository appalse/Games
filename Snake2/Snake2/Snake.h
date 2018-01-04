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

	void MakeStep(); // Move snake by 1 step in specified direction. 
	bool HasEaten(int x, int y) const;
	void Lengthen() { ++length; }
	bool HasIntersection() const;
	bool LengthTooLong() const;

	void SetSnakeDirection(const Direction& newDirection) { direction = newDirection; }
	int GetSnakeLength() const { return length; }
	int GetX(int position) const { return coords[position].x; }
	int GetY(int position) const { return coords[position].y; }
	std::string GetSnakeTexturePath() const { return snakeTexturePath; }

	// do not copy or move Snake
	Snake(const Snake& other) = delete;
	Snake& operator= (const Snake& other) = delete;
	Snake& operator= (Snake&& other) = delete;

private:
	const std::string snakeTexturePath = "images/snake2.png";
	int length;
	Direction direction;
	struct Coord { int x; int y; } coords[SNAKE_LENGTH_MAX];

	// proceed snake by 1 step on specified coordinate (x or y)
	void goAhead(int& coord, const int& maxCoordLength);
	void goBack(int& coord, const int& maxCoordLength);
};
