#pragma once
/* Snake class. Contains:
   - information about snake size and position
   - methods to move snake
*/

const int SNAKE_LENGTH_MIN = 4;
const int SNAKE_LENGTH_MAX = 20;

enum class Direction : int
{
	RIGHT,
	DOWN,
	LEFT,
	UP
};

class Snake {
public:
	Snake();

	void MakeStep(int cellsCoutByX, int cellsCountByY); // Move snake by 1 step in specified direction. 
	bool HasEaten(int x, int y) const;
	void Lengthen() { ++length; }
	bool HasIntersection() const;
	bool LengthTooLong() const;

	void SetSnakeDirection(const Direction& newDirection) { direction = newDirection; }
	Direction GetSnakeDirection() { return direction; }
	int GetSnakeLength() const { return length; }
	int GetX(int position) const { return coords[position].x; }
	int GetY(int position) const { return coords[position].y; }

	// do not copy or move Snake
	Snake(const Snake& other) = delete;
	Snake& operator= (const Snake& other) = delete;
	Snake& operator= (Snake&& other) = delete;

private:
	int length;
	Direction direction;
	// snake's coordinates positions
	struct Coord { int x; int y; } coords[SNAKE_LENGTH_MAX];

	// proceed snake by 1 step on specified coordinate (x or y)
	void goAhead(int& coord, const int& maxCoordLength);
	void goBack(int& coord, const int& maxCoordLength);
};
