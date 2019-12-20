#pragma once

#include <array>
#include <unordered_map>
#include "SceneNode.h"
#include "Tetromino.h"

namespace std
{
	template <>
	struct hash<sf::Vector2u>
	{
		std::size_t operator()(const sf::Vector2u& vector) const
		{
			// Compute individual hash values for x and y
			// and combine them using XOR and bit shifting
			return (std::hash<unsigned int>()(vector.x) ^ (hash<unsigned int>()(vector.y) << 1));
		}
	};
}

class Grid : public SceneNode
{
	public :
		struct Tile
		{
			sf::Color color = sf::Color::Transparent;
			unsigned int value = 0;
		};

		Grid();
		virtual ~Grid();

		bool addTetromino(std::unique_ptr<Tetromino> tetromino);
		bool moveCurrentTetromino(const sf::Vector2i& deltaPosition);
		bool rotateCurrentTetromino(bool clockWise = true);

		bool needNewTetromino() const;

		virtual Category getCategory() const;

	private :
		virtual void updateCurrent(sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		bool checkCollision(Tetromino* tetromino, const sf::Vector2u& position) const;
		void removeCompletedLines();
		std::size_t positionToIndex(const sf::Vector2u& position) const;

		static std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> initializeRotationWallKicks();
		static std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> initializeRotationWallKicksI();

		int mTimeSinceLastTetrominoMovement = 0;
		bool mNeedNewTetromino = false;

		const sf::Vector2u GRID_SIZE = sf::Vector2u(10, 22);

		std::array<Tile, 220> mTiles;
		std::unique_ptr<Tetromino> mCurrentTetromino = nullptr;
		sf::Vector2u mCurrentTetrominoPosition;
		sf::RectangleShape mGridRectangle;

		const std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> ROTATION_WALL_KICKS = initializeRotationWallKicks();
		const std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> ROTATION_WALL_KICKS_I = initializeRotationWallKicksI();
};

