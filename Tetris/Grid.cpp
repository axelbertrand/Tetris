#include "Grid.h"
#include "TetrominoFactory.h"

Grid::Grid()
	: mGridRectangle(sf::Vector2f(GRID_SIZE))
{
	mGridRectangle.scale(20.f, 20.f);
	mGridRectangle.setFillColor(sf::Color(128, 212, 255, 100));
	sf::FloatRect bounds = mGridRectangle.getLocalBounds();
	mGridRectangle.setOrigin(std::floor(bounds.left + bounds.width / 2.f), 0.f);
}

Grid::~Grid()
{
}

bool Grid::addTetromino(std::unique_ptr<Tetromino> tetromino)
{
	// Up-centered
	sf::Vector2u startingPosition(4, 0);
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
				std::size_t tileIndex = (startingPosition.x + j) * GRID_SIZE.y + (startingPosition.y + i);
				mTiles.at(tileIndex).color = tetromino->getColor();
				mTiles.at(tileIndex).value = tetromino->getValue();
			}
		}
	}

	mCurrentTetromino = tetromino.get();
	mTetrominos.insert(std::make_pair(startingPosition, std::move(tetromino)));
	mNeedNewTetromino = false;

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
				std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
				mTiles.at(tileIndex).value = 0;
				mTiles.at(tileIndex).color = sf::Color::Transparent;
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
					std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
					mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
					mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
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
				std::size_t tileIndex = (newPosition.x + j) * GRID_SIZE.y + (newPosition.y + i);
				mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
				mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
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
				std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
				mTiles.at(tileIndex).value = 0;
				mTiles.at(tileIndex).color = sf::Color::Transparent;
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
					std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
					mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
					mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
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
				std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
				mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
				mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
			}
		}
	}

	return true;
}

bool Grid::needNewTetromino() const
{
	return mNeedNewTetromino;
}

void Grid::updateCurrent(sf::Time dt)
{
	mTimeSinceLastTetrominoMovement += dt.asMilliseconds();

	if (mTimeSinceLastTetrominoMovement >= 1000)
	{
		if (!moveCurrentTetromino(sf::Vector2i(0, 1)))
		{
			mNeedNewTetromino = true;
		}

		mTimeSinceLastTetrominoMovement -= 1000;
	}
}

void Grid::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mGridRectangle, states);

	for (int x = 0; x < GRID_SIZE.x; ++x)
	{
		for (int y = 0; y < GRID_SIZE.y; ++y)
		{
			sf::RectangleShape tileRectangle({ 20.f, 20.f });
			tileRectangle.setPosition({ (x - static_cast<int>(GRID_SIZE.x / 2)) * 20.f, y * 20.f });
			tileRectangle.setFillColor(mTiles.at(x * GRID_SIZE.y + y).color);
			target.draw(tileRectangle, states);
		}
	}
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
					if (mTiles.at((position.x + j) * GRID_SIZE.y + (position.y + i)).value != 0)
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
