#pragma once
/* Game class. Contains game logic */

#include "GameGraphics.h"
#include "Eat.h"
#include "Snake.h"
#include <time.h>		/* clock_t, clock */
#include <iostream>


// Timeout in milliseconds
const int TIMEOUT = 100;

class Game {
public:
	Game();

	void Play();

private:
	// grid for snake hase size: cellsCountByY x cellsCountByX
	const int cellsCountByY = 20; 
	const int cellsCountByX = 20;
	// every grid's cell has size in pixels: cellSize x cellSize
	const int cellSize = 16; // in pixels
	// total width and height of window
	const int windowHeight = cellSize * cellsCountByY; // in pixels
	const int windowWidth = cellSize * cellsCountByX; // in pixels

	GameGraphics graphics;
	Snake snake;
	Eat eat;	

	// update snake state during specified period (see TIMEOUT)
	void tick(std::clock_t& currentTime, std::clock_t& startTime, Snake& snake, Eat& eat);
	// change snake direction after key pressing
	void processKeyPressed(Snake& snake);

	bool hasIntersection;
	bool snakeTooLong;
};
