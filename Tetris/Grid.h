#pragma once

#include <array>
#include <unordered_map>
#include <fstream>

#include "SceneNode.h"
#include "Tetromino.h"
#include "Utils.h"

class Grid : public SceneNode
{
public :
	struct Tile
	{
		sf::Color color{ sf::Color::Transparent };
		unsigned int value{ 0 };
	};

	Grid();

	bool addTetromino(std::unique_ptr<Tetromino> tetromino);
	bool moveCurrentTetromino(const sf::Vector2i& deltaPosition);
	bool hardDropCurrentTetromino();
	bool rotateCurrentTetromino(bool clockWise = true);

	bool needNewTetromino() const;
	unsigned int getCompletedLinesCount() const;
	void increaseSpeed();

	Category getCategory() const override;

	bool save(std::ofstream outputFileStream);
	bool load(std::ifstream inputFileStream);

private :
	void updateCurrent(sf::Time dt) override;
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	bool checkCollision(Tetromino* tetromino, const sf::Vector2u& position) const;
	unsigned int removeCompletedLines();
	std::size_t positionToIndex(const sf::Vector2u& position) const;

	static std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> initializeRotationWallKicks();
	static std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> initializeRotationWallKicksI();

	const sf::Vector2u GRID_SIZE{ 10, 22 };
	const double SPEED_MULTIPLIER{ 0.925874 };
	const std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> ROTATION_WALL_KICKS{ initializeRotationWallKicks() };
	const std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> ROTATION_WALL_KICKS_I{ initializeRotationWallKicksI() };

	int mTimeSinceLastTetrominoMovement{ 0 };
	bool mNeedNewTetromino{ false };
	unsigned int mCompletedLinesCount{ 0 };
	int mUpdateTime{ 1000 };

	std::array<Tile, 220> mTiles;
	std::unique_ptr<Tetromino> mCurrentTetromino{ nullptr };
	sf::Vector2u mCurrentTetrominoPosition;
	sf::RectangleShape mGridRectangle{ sf::Vector2f(GRID_SIZE) };
};

