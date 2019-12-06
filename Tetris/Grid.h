#pragma once

#include <array>
#include <unordered_map>
#include "SceneNode.h"
#include "Tetromino.h"

namespace std
{
	template <>
	struct hash<sf::Vector2i>
	{
		std::size_t operator()(const sf::Vector2i& vector) const
		{
			// Compute individual hash values for x and y
			// and combine them using XOR and bit shifting
			return (std::hash<int>()(vector.x) ^ (hash<int>()(vector.y) << 1));
		}
	};
}

class Grid : public SceneNode
{
	public :
		struct Tile
		{
			sf::Color color;
			int value;
		};

		Grid();
		virtual ~Grid();

		bool addTetromino(std::unique_ptr<Tetromino> tetromino);
		bool moveCurrentTetromino(const sf::Vector2i& deltaPosition);
		bool rotateCurrentTetromino(bool clockWise = true);

		Tetromino* getCurrentTetromino() const;

	private :
		virtual void updateCurrent(sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		bool checkCollision(Tetromino* tetromino, const sf::Vector2i& position) const;

		const sf::Vector2u GRID_SIZE = sf::Vector2u(10, 22);

		std::array<Tile, 220> mTiles;
		std::unordered_map<sf::Vector2i, std::unique_ptr<Tetromino>> mTetrominos;
		Tetromino* mCurrentTetromino;
		sf::RectangleShape mGridRect;
};

