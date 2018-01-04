#include <time.h>		/* clock_t, clock */
#include <chrono>		/* duration */
#include <thread>
#include <stdlib.h>     /* srand, rand */
#include <SFML/Graphics.hpp>
#include "Snake.h"

struct Eat {
	int x;
	int y;
};

Eat GenerateEat() {
	Eat eat;
	eat.x = rand() % W;
	eat.y = rand() % H;
	return eat;
}

void RedrawEat(sf::RenderWindow& window, sf::Sprite& eatSprite, const Eat& eat) {
	eatSprite.setPosition(eat.x * CellSize, eat.y * CellSize);
	window.draw(eatSprite);
}

void RedrawGrid(sf::RenderWindow& window, sf::Sprite& gridSprite) {
	
	for (int i = 0; i < W; ++i) {
		for (int j = 0; j < H; ++j) {
			gridSprite.setPosition(i * CellSize, j * CellSize);
			window.draw(gridSprite);
		}
	}
}

void RedrawSnake(sf::RenderWindow& window, sf::Sprite& snakeSprite, const Snake& snake) {
	for (int i = 0; i < snake.GetSnakeLength(); ++i) {
		snakeSprite.setPosition(snake.GetX(i) * CellSize, snake.GetY(i) * CellSize);
		window.draw(snakeSprite);
	}
}

bool Tick(std::clock_t& currentTime, std::clock_t& startTime, Snake& snake, Eat& eat) {
	bool isGameOver = false;
	currentTime = std::clock();
	if (std::chrono::duration<double, std::milli>(currentTime - startTime).count() > TIMEOUT) {
		snake.MakeStep();
		if (snake.HasEaten(eat.x, eat.y)) {
			snake.Lengthen();
			eat = GenerateEat();
		}
		isGameOver = snake.HasIntersection() || snake.LengthTooLong();
		startTime = std::clock();
		currentTime = std::clock();
	}
	return isGameOver;
}

void processKeyPressed(Snake& snake) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		snake.SetSnakeDirection(Direction::LEFT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		snake.SetSnakeDirection(Direction::RIGHT);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		snake.SetSnakeDirection(Direction::DOWN);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		snake.SetSnakeDirection(Direction::UP);
	}
}

sf::Sprite CreateSprite(sf::Texture& texture, const std::string& texturePath, int cellSize = -1) {
	if (cellSize == -1) {
		texture.loadFromFile(texturePath);
	} else {
		sf::IntRect r(0, 0, cellSize - 1, cellSize - 1);
		texture.loadFromFile(texturePath, r);
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	return sprite;
}

int main()
{
	/* initialize random seed: */
	srand(time(0));

	sf::RenderWindow window(sf::VideoMode(Width, Height), "Snake Game ~~~~:");

	sf::Texture t;
	sf::Sprite gridSprite = CreateSprite(t, CellTexturePath, CellSize);

	Snake snake;

	sf::Texture snakeTexture;
	sf::Sprite snakeSprite = CreateSprite(snakeTexture, snake.GetSnakeTexturePath(), CellSize);

	sf::Texture eatTexture;
	sf::Sprite eatSprite = CreateSprite(eatTexture, EatTexturePath, CellSize);

	sf::Texture wastedTexture;
	sf::Sprite wastedSprite = CreateSprite(wastedTexture, WastedTexturePath, CellSize * H);

	std::clock_t startTime = std::clock();
	std::clock_t currentTime = std::clock();

	Eat eat = GenerateEat();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		processKeyPressed(snake);
		bool isGameOver = Tick(currentTime, startTime, snake, eat);
		if (isGameOver) {
			window.clear();
			wastedSprite.setPosition(0, 0);
			window.draw(wastedSprite);
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(TIMEOUT*10*5));
			break;
		}
		window.clear();
		RedrawGrid(window, gridSprite);		
		RedrawSnake(window, snakeSprite, snake);
		RedrawEat(window, eatSprite, eat);
		window.display();		
	}

	return 0;
}
