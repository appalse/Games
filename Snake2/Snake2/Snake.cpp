#include "Snake.h"

Snake::Snake() :
	length(SNAKE_LENGTH_MIN),
	direction(Direction::DOWN)
{
	for (int i = 0; i < SNAKE_LENGTH_MAX; ++i) {
		coords[i].x = 0;
		coords[i].y = 0;
	}
}

void Snake::MakeStep() {
	// Move all snake parts except the snake's head (coords[0])
	for (int i = length - 1; i > 0; --i) {
		coords[i].x = coords[i - 1].x;
		coords[i].y = coords[i - 1].y;
	}
	// Move snake's head (coords[0])
	if (direction == Direction::LEFT) {
		goBack(coords[0].x, W);
	}
	if (direction == Direction::RIGHT) {
		goAhead(coords[0].x, W);
	}
	if (direction == Direction::DOWN) {
		goAhead(coords[0].y, H);
	}
	if (direction == Direction::UP) {
		goBack(coords[0].y, H);
	}
}

void Snake::goAhead(int& coord, const int& maxCoordLength) {
	coord = ++coord % maxCoordLength;
}
void Snake::goBack(int& coord, const int& maxCoordLength) {
	coord = --coord % maxCoordLength;
	if (coord < 0) {
		coord = maxCoordLength + coord;
	}
}

bool Snake::HasEaten(int x, int y) const {
	if (coords[0].x == x && coords[0].y == y) return true;
	return false;
}

bool Snake::HasIntersection() const {
	for (int i = 1; i < length; ++i) {
		if (coords[0].x == coords[i].x && coords[0].y == coords[i].y) return true;
	}
	return false;
}

bool Snake::LengthTooLong() const {
	if (length > SNAKE_LENGTH_MAX) return true;
	return false;
}