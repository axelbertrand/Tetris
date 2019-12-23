#include "Grid.h"

#include <cassert>
#include "TetrominoFactory.h"

Grid::Grid()
{
	mGridRectangle.scale(20.f, 20.f);
	mGridRectangle.setFillColor(sf::Color(128, 212, 255, 100));
	sf::FloatRect bounds = mGridRectangle.getLocalBounds();
	mGridRectangle.setOrigin(std::floor(bounds.left + bounds.width / 2.f), 0.f);
}

bool Grid::addTetromino(std::unique_ptr<Tetromino> tetromino)
{
	// Up-centered
	mCurrentTetromino = std::move(tetromino);
	mCurrentTetrominoPosition = { 4, 0 };
	if (checkCollision(mCurrentTetromino.get(), mCurrentTetrominoPosition))
	{
		return false;
	}

	mCurrentTetromino->forEachTile([this](const unsigned int i, const unsigned int j) {
		std::size_t tileIndex = positionToIndex({ mCurrentTetrominoPosition.x + j, mCurrentTetrominoPosition.y + i });
		mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
		mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
	});

	mNeedNewTetromino = false;

	return true;
}

bool Grid::moveCurrentTetromino(const sf::Vector2i& deltaPosition)
{
	sf::Vector2u newPosition(mCurrentTetrominoPosition.x + deltaPosition.x, mCurrentTetrominoPosition.y + deltaPosition.y);

	mCurrentTetromino->forEachTile([this](const unsigned int i, const unsigned int j) {
		std::size_t tileIndex = positionToIndex({ mCurrentTetrominoPosition.x + j, mCurrentTetrominoPosition.y + i });
		mTiles.at(tileIndex).value = 0;
		mTiles.at(tileIndex).color = sf::Color::Transparent;
	});

	if (checkCollision(mCurrentTetromino.get(), newPosition))
	{
		mCurrentTetromino->forEachTile([this](const unsigned int i, const unsigned int j) {
			std::size_t tileIndex = positionToIndex({ mCurrentTetrominoPosition.x + j, mCurrentTetrominoPosition.y + i });
			mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
			mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
		});

		return false;
	}

	mCurrentTetromino->forEachTile([this, &newPosition](const unsigned int i, const unsigned int j) {
		std::size_t tileIndex = positionToIndex({ newPosition.x + j, newPosition.y + i });
		mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
		mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
	});

	mCurrentTetrominoPosition = newPosition;

	return true;
}

bool Grid::hardDropCurrentTetromino()
{
	bool canMove = false;
	while (moveCurrentTetromino({ 0, 1 }))
	{
		canMove = true;
	}

	return canMove;
}

bool Grid::rotateCurrentTetromino(bool clockWise)
{
	mCurrentTetromino->forEachTile([this](const unsigned int i, const unsigned int j) {
		std::size_t tileIndex = positionToIndex({ mCurrentTetrominoPosition.x + j, mCurrentTetrominoPosition.y + i });
		mTiles.at(tileIndex).value = 0;
		mTiles.at(tileIndex).color = sf::Color::Transparent;
	});

	mCurrentTetromino->rotate(clockWise);

	sf::Vector2u rotationPair(mCurrentTetromino->getRotationState(), (mCurrentTetromino->getRotationState() + ((clockWise) ? 1 : -1)) % 4);
	std::array<sf::Vector2i, 5> collisionTests = (mCurrentTetromino->getType() == Tetromino::Type::I) ? ROTATION_WALL_KICKS_I.at(rotationPair) : ROTATION_WALL_KICKS.at(rotationPair);

	for (const sf::Vector2i& translation : collisionTests)
	{
		sf::Vector2u newPosition(mCurrentTetrominoPosition.x + translation.x, mCurrentTetrominoPosition.y + translation.y);
		if (!checkCollision(mCurrentTetromino.get(), newPosition))
		{
			mCurrentTetromino->forEachTile([this, &newPosition](const unsigned int i, const unsigned int j) {
				std::size_t tileIndex = positionToIndex({ newPosition.x + j, newPosition.y + i });
				mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
				mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
			});

			mCurrentTetrominoPosition = newPosition;

			return true;
		}
	}

	mCurrentTetromino->rotate(!clockWise);

	mCurrentTetromino->forEachTile([this](const unsigned int i, const unsigned int j) {
		std::size_t tileIndex = positionToIndex({ mCurrentTetrominoPosition.x + j, mCurrentTetrominoPosition.y + i });
		mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
		mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
	});

	return false;
}

bool Grid::needNewTetromino() const
{
	return mNeedNewTetromino;
}

Category Grid::getCategory() const
{
	return Category::Grid;
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

		if (mNeedNewTetromino)
		{
			removeCompletedLines();
		}

		mTimeSinceLastTetrominoMovement -= 1000;
	}
}

void Grid::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mGridRectangle, states);

	for (int x = 0; x < static_cast<int>(GRID_SIZE.x); ++x)
	{
		for (int y = 0; y < static_cast<int>(GRID_SIZE.y); ++y)
		{
			sf::RectangleShape tileRectangle({ 20.f, 20.f });
			tileRectangle.setPosition({ (x - static_cast<int>(GRID_SIZE.x / 2)) * 20.f, y * 20.f });
			tileRectangle.setFillColor(mTiles.at(positionToIndex(sf::Vector2u(x, y))).color);
			target.draw(tileRectangle, states);
		}
	}
}

bool Grid::checkCollision(Tetromino* tetromino, const sf::Vector2u& position) const
{
	bool hasCollision = false;

	tetromino->forEachTile([this, &position, &hasCollision](const unsigned int i, const unsigned int j) {
		if (position.x + j < GRID_SIZE.x && position.y + i < GRID_SIZE.y)
		{
			if (mTiles.at(positionToIndex({ position.x + j, position.y + i })).value != 0)
			{
				hasCollision = true;
				return;
			}
		}
		else
		{
			hasCollision = true;
			return;
		}
	});

	return hasCollision;
}

void Grid::removeCompletedLines()
{
	unsigned int totalLineCount = 0;
	unsigned int lastCompletedLine = GRID_SIZE.y - 1;
	for (unsigned int i = GRID_SIZE.y - 1; i != static_cast<unsigned int>(-1); --i)
	{
		if (totalLineCount >= 4)
		{
			break;
		}

		// Check if line is completed
		bool isLineCompleted = true;
		for (unsigned int j = 0; j < GRID_SIZE.x; ++j)
		{
			if (mTiles.at(positionToIndex({ j, i })).value == 0) {
				isLineCompleted = false;
				break;
			}
		}

		if (isLineCompleted)
		{
			for (unsigned int k = i; k != 0; --k)
			{
				for (unsigned int j = 0; j < GRID_SIZE.x; ++j)
				{
					mTiles.at(positionToIndex({ j, k })).value = mTiles.at(positionToIndex({ j, k - 1 })).value;
					mTiles.at(positionToIndex({ j, k })).color = mTiles.at(positionToIndex({ j, k - 1 })).color;
				}
			}

			++totalLineCount;
			++i;
		}
	}
}

std::size_t Grid::positionToIndex(const sf::Vector2u& position) const
{
	return position.y * GRID_SIZE.x + position.x;
}

std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> Grid::initializeRotationWallKicks()
{
	std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> rotationWallKicks;

	rotationWallKicks[{ 0, 1 }] = { sf::Vector2i{ 0, 0 }, { -1, 0 }, { -1,  1 }, { 0, -2 }, { -1, -2 } };
	rotationWallKicks[{ 1, 0 }] = { sf::Vector2i{ 0, 0 }, {  1, 0 }, {  1, -1 }, { 0,  2 }, {  1,  2 } };
	rotationWallKicks[{ 1, 2 }] = { sf::Vector2i{ 0, 0 }, {  1, 0 }, {  1, -1 }, { 0,  2 }, {  1,  2 } };
	rotationWallKicks[{ 2, 1 }] = { sf::Vector2i{ 0, 0 }, { -1, 0 }, { -1,  1 }, { 0, -2 }, { -1, -2 } };
	rotationWallKicks[{ 2, 3 }] = { sf::Vector2i{ 0, 0 }, {  1, 0 }, {  1,  1 }, { 0, -2 }, {  1, -2 } };
	rotationWallKicks[{ 3, 2 }] = { sf::Vector2i{ 0, 0 }, { -1, 0 }, { -1, -1 }, { 0,  2 }, { -1,  2 } };
	rotationWallKicks[{ 3, 0 }] = { sf::Vector2i{ 0, 0 }, { -1, 0 }, { -1, -1 }, { 0,  2 }, { -1,  2 } };
	rotationWallKicks[{ 0, 3 }] = { sf::Vector2i{ 0, 0 }, {  1, 0 }, {  1,  1 }, { 0, -2 }, {  1, -2 } };

	return rotationWallKicks;
}

std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> Grid::initializeRotationWallKicksI()
{
	std::unordered_map<sf::Vector2u, std::array<sf::Vector2i, 5>> rotationWallKicksI;

	rotationWallKicksI[{ 0, 1 }] = { sf::Vector2i{ 0, 0 }, { -2, 0 }, {  1, 0 }, { -2, -1 }, {  1,  2 } };
	rotationWallKicksI[{ 1, 0 }] = { sf::Vector2i{ 0, 0 }, {  2, 0 }, { -1, 0 }, {  2,  1 }, { -1, -2 } };
	rotationWallKicksI[{ 1, 2 }] = { sf::Vector2i{ 0, 0 }, { -1, 0 }, {  2, 0 }, { -1,  2 }, {  2, -1 } };
	rotationWallKicksI[{ 2, 1 }] = { sf::Vector2i{ 0, 0 }, {  1, 0 }, { -2, 0 }, {  1, -2 }, { -2,  1 } };
	rotationWallKicksI[{ 2, 3 }] = { sf::Vector2i{ 0, 0 }, {  2, 0 }, { -1, 0 }, {  2,  1 }, { -1, -2 } };
	rotationWallKicksI[{ 3, 2 }] = { sf::Vector2i{ 0, 0 }, { -2, 0 }, {  1, 0 }, { -2, -1 }, {  1,  2 } };
	rotationWallKicksI[{ 3, 0 }] = { sf::Vector2i{ 0, 0 }, {  1, 0 }, { -2, 0 }, {  1, -2 }, { -2,  1 } };
	rotationWallKicksI[{ 0, 3 }] = { sf::Vector2i{ 0, 0 }, { -1, 0 }, {  2, 0 }, { -1,  2 }, {  2, -1 } };

	return rotationWallKicksI;
}
