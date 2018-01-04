#include <SFML/Graphics.hpp>
#include <ctime>
#include <chrono>
#include "Snake.h"

void RedrawGrid(sf::RenderWindow& window, sf::Sprite& gridSprite) {
	window.clear();
	for (int i = 0; i < W; ++i) {
		for (int j = 0; j < H; ++j) {
			gridSprite.setPosition(i * CellSize, j * CellSize);
			window.draw(gridSprite);
		}
	}
}

void RedrawSnake(sf::RenderWindow& window, sf::Sprite& snakeSprite, const Snake& snake) {
	for (int i = 0; i < snake.GetLength(); ++i) {
		snakeSprite.setPosition(snake.GetX(i) * CellSize, snake.GetY(i) * CellSize);
		window.draw(snakeSprite);
	}
}

void Tick(std::clock_t& currentTime, std::clock_t& startTime, Snake& snake) {
	currentTime = std::clock();
	if (std::chrono::duration<double, std::milli>(currentTime - startTime).count() > TIMEOUT) {
		snake.MakeStep();
		startTime = std::clock();
		currentTime = std::clock();
	}
}

void processKeyPressed(Snake& snake) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		snake.SetCurrentDirection(Direction::LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		snake.SetCurrentDirection(Direction::RIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		snake.SetCurrentDirection(Direction::DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		snake.SetCurrentDirection(Direction::UP);
	}
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(Width, Height), "Snake");

	sf::IntRect r(0, 0, CellSize - 1, CellSize - 1);

	sf::Texture t;
	t.loadFromFile(CellTexturePath, r);
	sf::Sprite gridSprite;
	gridSprite.setTexture(t);

	Snake snake;

	sf::Texture snakeTexture;
	snakeTexture.loadFromFile(snake.GetSnakeTexturePath(), r);
	sf::Sprite snakeSprite;
	snakeSprite.setTexture(snakeTexture);

	std::clock_t startTime = std::clock();
	std::clock_t currentTime = std::clock();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		processKeyPressed(snake);
		Tick(currentTime, startTime, snake);
		RedrawGrid(window, gridSprite);		
		RedrawSnake(window, snakeSprite, snake);
		window.display();		
	}

	return 0;
}
