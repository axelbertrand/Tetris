#include "Grid.h"
#include "TetrominoFactory.h"

Grid::Grid()
	: mGridRect(sf::Vector2f(GRID_SIZE.x, GRID_SIZE.y))
{
	mGridRect.scale(20.f, 20.f);
	mGridRect.setFillColor(sf::Color(128, 212, 255, 100));
	sf::FloatRect bounds = mGridRect.getLocalBounds();
	mGridRect.setOrigin(std::floor(bounds.left + bounds.width / 2.f), 0.f);
}

Grid::~Grid()
{
}

bool Grid::addTetromino(std::unique_ptr<Tetromino> tetromino)
{
	sf::Vector2i startingPosition(5, 0);
	if (checkCollision(tetromino.get(), startingPosition))
	{
		return false;
	}

	mTetrominos.push_back(std::move(tetromino));
	mTetrominosPosition.push_back(startingPosition);

	std::bitset<16> tetrominoShape = tetromino->getShape();
	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			if (tetrominoShape.test(i * 4 + j))
			{
				Tile& tile = mTiles.at((startingPosition.x + i) * 4 + (startingPosition.y + j));
				tile.color = tetromino->getColor();
				tile.value = tetromino->getValue();
			}
		}
	}

	return true;
}

void Grid::updateCurrent(sf::Time dt)
{

}

void Grid::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mGridRect, states);
}

bool Grid::checkCollision(Tetromino* tetromino, sf::Vector2i position) const
{
	std::bitset<16> tetrominoShape = tetromino->getShape();

	for (std::size_t i = 0; i < 4; i++) {
		for (std::size_t j = 0; j < 4; j++) {
			if (tetrominoShape.test(i * 4 + j)) {
				if (position.x + i < GRID_SIZE.x && position.y + j < GRID_SIZE.y) {
					if (mTiles.at((position.x + i) * 4 + (position.y + j)).value != 0) {
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		}
	}

	return false;
}
