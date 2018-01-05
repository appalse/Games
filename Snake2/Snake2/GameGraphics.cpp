#include "GameGraphics.h"

const std::string CellTexturePath = "images/sand.png";
const std::string EatTexturePath = "images/eat.png";
const std::string WastedTexturePath = "images/wasted.png";
const std::string CongratulationsTexturePath = "images/congratulations.png";
const std::string SnakeTexturePath = "images/snake2.png";

GameGraphics::GameGraphics(int w, int h, int initCellSize) :
	windowWidth(w),
	windowHeight(h),
	cellSize(initCellSize)
{
	window.create(sf::VideoMode(windowWidth, windowHeight), "Snake Game ~~~~:");
	gridSprite = createSprite(gridTexture, CellTexturePath, cellSize);
	snakeSprite = createSprite(snakeTexture, SnakeTexturePath, cellSize);
	eatSprite = createSprite(eatTexture, EatTexturePath, cellSize);
}

sf::Sprite GameGraphics::createSprite(sf::Texture& texture, const std::string& texturePath, int spriteCellsize) {
	if (spriteCellsize == -1) {
		texture.loadFromFile(texturePath);
	}
	else {
		sf::IntRect r(0, 0, spriteCellsize - 1, spriteCellsize - 1);
		texture.loadFromFile(texturePath, r);
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);
	return sprite;
}

void GameGraphics::CheckForCloseEvent() {
	sf::Event event;
	while (window.pollEvent(event))	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void GameGraphics::RedrawEat(int x, int y) {
	eatSprite.setPosition(static_cast<float>(x * cellSize), static_cast<float>(y * cellSize));
	window.draw(eatSprite);
}

void GameGraphics::RedrawGrid(int CellsCountByX, int CellsCountByY) {
	for (int i = 0; i < CellsCountByX; ++i) {
		for (int j = 0; j < CellsCountByY; ++j) {
			gridSprite.setPosition(static_cast<float>(i * cellSize), static_cast<float>(j * cellSize));
			window.draw(gridSprite);
		}
	}
}

void GameGraphics::RedrawSnake(const Snake& snake) {
	int snakeLength = snake.GetSnakeLength();
	for (int i = 0; i < snakeLength; ++i) {
		snakeSprite.setPosition(static_cast<float>(snake.GetX(i) * cellSize), static_cast<float>(snake.GetY(i) * cellSize));
		window.draw(snakeSprite);
	}
}

void GameGraphics::DrawResult(bool isSuccess, int CellsCountByX, int CellsCountByY) {
	std::string resultTexturePath;
	isSuccess ? resultTexturePath = CongratulationsTexturePath : resultTexturePath = WastedTexturePath;
	sf::Texture resultTexture;
	sf::Sprite resultSprite = createSprite(resultTexture, resultTexturePath); // , cellSize * H

	window.clear();
	centralizeSprite(resultSprite);
	window.draw(resultSprite);
	window.display();
}

void GameGraphics::centralizeSprite(sf::Sprite& sprite)
{
	sf::Vector2u windowSize = window.getSize();
	sf::IntRect textureRect = sprite.getTextureRect();
	sprite.setPosition(static_cast<float>(windowSize.x / 2 - textureRect.width / 2), static_cast<float>(windowSize.y / 2 - textureRect.height / 2));
}