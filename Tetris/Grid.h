#pragma once

#include <array>
#include <vector>
#include "SceneNode.h"
#include "Tetromino.h"

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

	private :
		virtual void updateCurrent(sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		bool checkCollision(Tetromino* tetromino, sf::Vector2i position) const;

		const sf::Vector2i GRID_SIZE = sf::Vector2i(10, 22);

		std::array<Tile, 220> mTiles;
		std::vector<std::unique_ptr<Tetromino>> mTetrominos;
		std::vector<sf::Vector2i> mTetrominosPosition;
		sf::RectangleShape mGridRect;
};

