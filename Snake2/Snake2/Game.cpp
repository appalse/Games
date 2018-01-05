#include "Game.h"
#include <chrono>		/* duration */
#include <iostream>


Game::Game() :
	graphics(windowWidth, windowHeight, cellSize),
	snake(),
	eat(cellsCountByX, cellsCountByY)
{
}

void Game::processKeyPressed(Snake& snake) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && snake.GetSnakeDirection() != Direction::RIGHT) {
		snake.SetSnakeDirection(Direction::LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && snake.GetSnakeDirection() != Direction::LEFT) {
		snake.SetSnakeDirection(Direction::RIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && snake.GetSnakeDirection() != Direction::UP) {
		snake.SetSnakeDirection(Direction::DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && snake.GetSnakeDirection() != Direction::DOWN) {
		snake.SetSnakeDirection(Direction::UP);
	}
}

void Game::tick(std::clock_t& currentTime, std::clock_t& startTime, Snake& snake, Eat& eat) {
	currentTime = std::clock();
	if (std::chrono::duration<double, std::milli>(currentTime - startTime).count() > TIMEOUT) {
		snake.MakeStep(cellsCountByX, cellsCountByY);
		if (snake.HasEaten(eat.GetX(), eat.GetY())) {
			snake.Lengthen();
			eat.GenerateNewCoordinates();
		}
		hasIntersection = snake.HasIntersection();
		snakeTooLong = snake.LengthTooLong();
		startTime = std::clock();
		currentTime = std::clock();
	}
}

void Game::Play() {
	bool isSucess = false;
	std::clock_t startTime = std::clock();
	std::clock_t currentTime = std::clock();

	while (graphics.IsGameWindowOpened())
	{
		graphics.CheckForCloseEvent();
		processKeyPressed(snake);

		tick(currentTime, startTime, snake, eat);

		if (hasIntersection) {
			std::cout << "Has intersection" << std::endl;
			break;
		}
		if (snakeTooLong) {
			std::cout << "Snake Length is long enough. You win " << std::endl;
			isSucess = true;
			break;
		}
		graphics.ClearWindow();
		graphics.RedrawGrid(cellsCountByX, cellsCountByY);
		graphics.RedrawSnake(snake);
		graphics.RedrawEat(eat.GetX(), eat.GetY());
		graphics.DisplayWindow();
	}
	graphics.DrawResult(isSucess, cellsCountByX, cellsCountByY);
}

