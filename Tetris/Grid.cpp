#include "Grid.h"
#include "TetrominoFactory.h"

Grid::Grid()
	: mGridRect(sf::Vector2f(GRID_SIZE))
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
	sf::Vector2u startingPosition(5, 0);
	if (checkCollision(tetromino.get(), startingPosition))
	{
		return false;
	}

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

	mCurrentTetromino = tetromino.get();
	mTetrominos.insert(std::make_pair(startingPosition, std::move(tetromino)));

	return true;
}

bool Grid::moveCurrentTetromino(const sf::Vector2i& deltaPosition)
{
	std::bitset<16> tetrominoShape = mCurrentTetromino->getShape();

	// Search for the current tetromino position
	auto foundIterator = std::find_if(mTetrominos.begin(), mTetrominos.end(), [this](const auto& tetrominoPair) {
		return tetrominoPair.second.get() == mCurrentTetromino;
	});

	if (foundIterator == mTetrominos.end())
	{
		return false;
	}

	sf::Vector2u currentTetrominoPosition = foundIterator->first;

	sf::Vector2u newPosition(currentTetrominoPosition.x + deltaPosition.x, currentTetrominoPosition.y + deltaPosition.y);

	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			if (tetrominoShape.test(i * 4 + j))
			{
				Tile& oldTile = mTiles.at((currentTetrominoPosition.x + i) * 4 + (currentTetrominoPosition.y + j));
				oldTile.value = 0;
				oldTile.color = sf::Color::Transparent;
			}
		}
	}

	if (checkCollision(mCurrentTetromino, newPosition))
	{
		for (std::size_t i = 0; i < 4; ++i)
		{
			for (std::size_t j = 0; j < 4; ++j)
			{
				if (tetrominoShape.test(i * 4 + j))
				{
					Tile& oldTile = mTiles.at((currentTetrominoPosition.x + i) * 4 + (currentTetrominoPosition.y + j));
					oldTile.value = mCurrentTetromino->getValue();
					oldTile.color = mCurrentTetromino->getColor();
				}
			}
		}

		return false;
	}

	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			if (tetrominoShape.test(i * 4 + j))
			{
				Tile& newTile = mTiles.at((newPosition.x + i) * 4 + (newPosition.y + j));
				newTile.value = mCurrentTetromino->getValue();
				newTile.color = mCurrentTetromino->getColor();
			}
		}
	}

	// Change the position of the tetromino to its new position
	auto nodeHandle = mTetrominos.extract(currentTetrominoPosition);
	nodeHandle.key() = newPosition;
	mTetrominos.insert(std::move(nodeHandle));

	return true;
}

bool Grid::rotateCurrentTetromino(bool clockWise)
{
	std::bitset<16> tetrominoShape = mCurrentTetromino->getShape();

	// Search for the current tetromino position
	auto foundIterator = std::find_if(mTetrominos.begin(), mTetrominos.end(), [this](const auto& tetrominoPair) {
		return tetrominoPair.second.get() == mCurrentTetromino;
	});

	if (foundIterator == mTetrominos.end())
	{
		return false;
	}

	sf::Vector2u currentTetrominoPosition = foundIterator->first;

	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			if (tetrominoShape.test(i * 4 + j))
			{
				Tile& oldTile = mTiles.at((currentTetrominoPosition.x + i) * 4 + (currentTetrominoPosition.y + j));
				oldTile.value = 0;
				oldTile.color = sf::Color::Transparent;
			}
		}
	}

	mCurrentTetromino->rotate(clockWise);

	if (checkCollision(mCurrentTetromino, currentTetrominoPosition))
	{
		for (std::size_t i = 0; i < 4; ++i)
		{
			for (std::size_t j = 0; j < 4; ++j)
			{
				if (tetrominoShape.test(i * 4 + j))
				{
					Tile& oldTile = mTiles.at((currentTetrominoPosition.x + i) * 4 + (currentTetrominoPosition.y + j));
					oldTile.value = mCurrentTetromino->getValue();
					oldTile.color = mCurrentTetromino->getColor();
				}
			}
		}

		mCurrentTetromino->rotate(!clockWise);

		return false;
	}

	tetrominoShape = mCurrentTetromino->getShape();

	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			if (tetrominoShape.test(i * 4 + j))
			{
				Tile& newTile = mTiles.at((currentTetrominoPosition.x + i) * 4 + (currentTetrominoPosition.y + j));
				newTile.value = mCurrentTetromino->getValue();
				newTile.color = mCurrentTetromino->getColor();
			}
		}
	}

	return true;
}

Tetromino* Grid::getCurrentTetromino() const
{
	return mCurrentTetromino;
}

void Grid::updateCurrent(sf::Time dt)
{

}

void Grid::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mGridRect, states);
}

bool Grid::checkCollision(Tetromino* tetromino, const sf::Vector2u& position) const
{
	std::bitset<16> tetrominoShape = tetromino->getShape();

	for (std::size_t i = 0; i < 4; ++i)
	{
		for (std::size_t j = 0; j < 4; ++j)
		{
			if (tetrominoShape.test(i * 4 + j))
			{
				if (position.x + i < GRID_SIZE.x && position.y + j < GRID_SIZE.y)
				{
					if (mTiles.at((position.x + i) * 4 + (position.y + j)).value != 0)
					{
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
