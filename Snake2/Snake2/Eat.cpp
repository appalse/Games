#include "Eat.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>


Eat::Eat(int width, int height) :
	cellsCountByX(width),
	cellsCountByY(height)
{
	// initialize random seed
	srand(static_cast<unsigned int>(time(0)));
	GenerateNewCoordinates();
}

void Eat::GenerateNewCoordinates() {
	x = rand() % cellsCountByX;
	y = rand() % cellsCountByY;
}