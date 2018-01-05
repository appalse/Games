#pragma once
/* Eat class. Contains coordinates of eat. Can regenerate new random coordinates */
#include <stdlib.h>     /* srand, rand */

class Eat {
public:
	Eat(int width, int height);
	
	int GetX() const { return x; }
	int GetY() const { return y; }

	void GenerateNewCoordinates();

private:
	int x;
	int y;
	const int cellsCountByX;
	const int cellsCountByY;
};

