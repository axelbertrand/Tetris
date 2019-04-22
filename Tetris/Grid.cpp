#include "Grid.h"
#include "TetrominoFactory.h"

Grid::Grid() :
mGridRect(sf::Vector2f(10.f, 22.f)),
mCurrentTetromino(nullptr),
mElapsedTime(0),
mNeedNewTetromino(true)
{
	mGridRect.scale(20.f, 20.f);
	mGridRect.setFillColor(sf::Color(128, 212, 255, 100));
	sf::FloatRect bounds = mGridRect.getLocalBounds();
	mGridRect.setOrigin(std::floor(bounds.left + bounds.width / 2.f), 0.f);
}

Grid::~Grid()
{
}

void Grid::setSquareScale(float scale)
{
	mGridRect.setScale(10.f * scale, 22.f * scale);
}

void Grid::addTetromino(Tetromino::Ptr tetromino)
{
	tetromino->setScale(mGridRect.getScale());

	mCurrentTetromino = tetromino.get();
	attachChild(std::move(tetromino));

	mNeedNewTetromino = false;
}

bool Grid::needNewTetromino() const
{
	return mNeedNewTetromino;
}

sf::FloatRect Grid::getBoundingRect() const
{
	//return mGridRect.getGlobalBounds();
	return getWorldTransform().transformRect(mGridRect.getGlobalBounds());
}

Tetromino* Grid::getCurrentTetromino() const
{
	return mCurrentTetromino;
}

void Grid::updateCurrent(sf::Time dt)
{
	//adaptTetrominoPosition();

	mElapsedTime += dt.asMilliseconds();

	if (mElapsedTime >= 1000)
	{
		if (mCurrentTetromino->getPosition().y + mCurrentTetromino->getBoundingRect().height <= getBoundingRect().height)
		{
			mCurrentTetromino->move(0.f, 20.f);
		}
		else
		{
			mNeedNewTetromino = true;
			mCurrentTetromino->setPlaced(true);
		}

		mElapsedTime -= 1000;
	}
}

void Grid::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mGridRect, states);
}

void Grid::adaptTetrominoPosition()
{
	sf::FloatRect gridBounds = mGridRect.getGlobalBounds();

	sf::Vector2f position = mCurrentTetromino->getPosition();
	/*sf::FloatRect tetrominoBounds = mCurrentTetromino->getBoundingRect();
	sf::Vector2f origin = mCurrentTetromino->getOrigin();
	sf::Vector2f scale = mCurrentTetromino->getScale();*/

	position.x = std::max(position.x, gridBounds.left);
	position.x = std::min(position.x, gridBounds.left + gridBounds.width);
	position.y = std::max(position.y, gridBounds.top); // + (origin.y + static_cast<int>(currentTetromino->getRotation()) / 180) * scale.y
	position.y = std::min(position.y, gridBounds.top + gridBounds.height); // + (origin.y + static_cast<int>(currentTetromino->getRotation()) / 180) * scale.y - tetrominoBounds.height
	mCurrentTetromino->setPosition(position);
}
