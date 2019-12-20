#include "Grid.h"

#include <cassert>
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

	tetromino->forEachTile([this, &tetromino, &startingPosition](const std::size_t i, const std::size_t j) {
		std::size_t tileIndex = (startingPosition.x + j) * GRID_SIZE.y + (startingPosition.y + i);
		mTiles.at(tileIndex).color = tetromino->getColor();
		mTiles.at(tileIndex).value = tetromino->getValue();
	});

	mCurrentTetromino = tetromino.get();
	mTetrominos.insert(std::make_pair(startingPosition, std::move(tetromino)));
	mNeedNewTetromino = false;

	return true;
}

bool Grid::moveCurrentTetromino(const sf::Vector2i& deltaPosition)
{
	sf::Vector2u currentTetrominoPosition = getCurrentTetrominoPosition();

	sf::Vector2u newPosition(currentTetrominoPosition.x + deltaPosition.x, currentTetrominoPosition.y + deltaPosition.y);

	mCurrentTetromino->forEachTile([this, &currentTetrominoPosition](const std::size_t i, const std::size_t j) {
		std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
		mTiles.at(tileIndex).value = 0;
		mTiles.at(tileIndex).color = sf::Color::Transparent;
	});

	if (checkCollision(mCurrentTetromino, newPosition))
	{
		mCurrentTetromino->forEachTile([this, &currentTetrominoPosition](const std::size_t i, const std::size_t j) {
			std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
			mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
			mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
		});

		return false;
	}

	mCurrentTetromino->forEachTile([this, &newPosition](const std::size_t i, const std::size_t j) {
		std::size_t tileIndex = (newPosition.x + j) * GRID_SIZE.y + (newPosition.y + i);
		mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
		mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
	});

	updateTetrominoPositionMapping(currentTetrominoPosition, newPosition);

	return true;
}

bool Grid::rotateCurrentTetromino(bool clockWise)
{
	sf::Vector2u currentTetrominoPosition = getCurrentTetrominoPosition();

	mCurrentTetromino->forEachTile([this, &currentTetrominoPosition](const std::size_t i, const std::size_t j) {
		std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
		mTiles.at(tileIndex).value = 0;
		mTiles.at(tileIndex).color = sf::Color::Transparent;
	});

	mCurrentTetromino->rotate(clockWise);

	sf::Vector2u rotationPair(mCurrentTetromino->getRotationState(), (mCurrentTetromino->getRotationState() + ((clockWise) ? 1 : -1)) % 4);
	std::array<sf::Vector2i, 5> collisionTests = (mCurrentTetromino->getType() == Tetromino::Type::I) ? ROTATION_WALL_KICKS_I.at(rotationPair) : ROTATION_WALL_KICKS.at(rotationPair);

	for (const sf::Vector2i& translation : collisionTests)
	{
		sf::Vector2u newPosition(currentTetrominoPosition.x + translation.x, currentTetrominoPosition.y + translation.y);
		if (!checkCollision(mCurrentTetromino, newPosition))
		{
			mCurrentTetromino->forEachTile([this, &newPosition](const std::size_t i, const std::size_t j) {
				std::size_t tileIndex = (newPosition.x + j) * GRID_SIZE.y + (newPosition.y + i);
				mTiles.at(tileIndex).value = mCurrentTetromino->getValue();
				mTiles.at(tileIndex).color = mCurrentTetromino->getColor();
			});

			updateTetrominoPositionMapping(currentTetrominoPosition, newPosition);

			return true;
		}
	}

	mCurrentTetromino->rotate(!clockWise);

	mCurrentTetromino->forEachTile([this, &currentTetrominoPosition](const std::size_t i, const std::size_t j) {
		std::size_t tileIndex = (currentTetrominoPosition.x + j) * GRID_SIZE.y + (currentTetrominoPosition.y + i);
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
	bool hasCollision = false;

	tetromino->forEachTile([this, &position, &hasCollision](const std::size_t i, const std::size_t j) {
		if (position.x + j < GRID_SIZE.x && position.y + i < GRID_SIZE.y)
		{
			if (mTiles.at((position.x + j) * GRID_SIZE.y + (position.y + i)).value != 0)
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

void Grid::updateTetrominoPositionMapping(const sf::Vector2u& oldPosition, const sf::Vector2u& newPosition)
{
	auto nodeHandle = mTetrominos.extract(oldPosition);
	nodeHandle.key() = newPosition;
	mTetrominos.insert(std::move(nodeHandle));
}

sf::Vector2u Grid::getCurrentTetrominoPosition() const
{
	auto foundIterator = std::find_if(mTetrominos.begin(), mTetrominos.end(), [this](const auto& tetrominoPair) {
		return tetrominoPair.second.get() == mCurrentTetromino;
	});

	assert(foundIterator != mTetrominos.end());

	return foundIterator->first;
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
