#pragma once
/* Game graphics class. Contains data and methods for drawing graphics via SFML library */

#include <SFML/Graphics.hpp>
#include <string>
#include "Snake.h"

class GameGraphics {
public:
	GameGraphics(int w, int h, int initCellSize);

	bool IsGameWindowOpened() { return window.isOpen(); }
	void CheckForCloseEvent();

	void ClearWindow() { window.clear(); }
	void DisplayWindow() { window.display(); }

	// Painting elements
	void RedrawEat(int x, int y);
	void RedrawGrid(int CellsCountByX, int CellsCountByY);
	void RedrawSnake(const Snake& snake);
	void DrawResult(bool isSuccess, int CellsCountByX, int CellsCountByY);
private:
	const int windowWidth; // in pixels
	const int windowHeight; // in pixels	
	const int cellSize; // in pixels

	sf::RenderWindow window;
	sf::Texture gridTexture; // time of life of Texture object should be the same as for Sprite object
	sf::Sprite gridSprite;
	sf::Texture snakeTexture;
	sf::Sprite snakeSprite;
	sf::Texture eatTexture;
	sf::Sprite eatSprite;
	sf::Texture wastedTexture;
	sf::Sprite wastedSprite;
	sf::Texture congratulationsTexture;
	sf::Sprite congratulationsSprite;

	// function to create some sprite
	sf::Sprite createSprite(sf::Texture& texture, const std::string& texturePath, int spriteCellsize = -1);
	// set image position in the center of window
	void centralizeSprite(sf::Sprite& sprite);
};
