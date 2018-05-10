#include "Grid.h"
#include "TetrominoFactory.h"

Grid::Grid() :
mGridRect(sf::Vector2f(10.f, 22.f)),
mTetrominos(),
mCurrentTetromino(-1),
mElapsedTime(0),
mNeedNewTetromino(true)
{
	mGridRect.scale(20.f, 20.f);
	mGridRect.setFillColor(sf::Color(128, 212, 255, 100));
	sf::FloatRect bounds = mGridRect.getLocalBounds();
	mGridRect.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

Grid::~Grid()
{
}

void Grid::setSquareScale(float scale)
{
	mGridRect.setScale(10.f * scale, 22.f * scale);
}

void Grid::add(Tetromino::Ptr tetromino)
{
	sf::FloatRect gridBounds = mGridRect.getLocalBounds();
	tetromino->setOrigin(std::floor(gridBounds.left + gridBounds.width / 2.f), std::floor(gridBounds.top + gridBounds.height / 2.f));
	tetromino->setScale(mGridRect.getScale());
	tetromino->setPosition(std::floor((gridBounds.width - tetromino->getLocalBounds().width) / 2.f) * mGridRect.getScale().x, 0.f);

	mTetrominos.push_back(tetromino);
	mCurrentTetromino++;

	mNeedNewTetromino = false;
}

bool Grid::needNewTetromino() const
{
	return mNeedNewTetromino;
}

void Grid::updateCurrent(sf::Time dt)
{
	mElapsedTime += dt.asMilliseconds();

	if (mElapsedTime >= 1000)
	{
		if (mTetrominos[mCurrentTetromino]->getPosition().y + mTetrominos[mCurrentTetromino]->getGlobalBounds().height < mGridRect.getGlobalBounds().height)
		{
			mTetrominos[mCurrentTetromino]->move(0.f, 20.f);
		}
		else
		{
			mNeedNewTetromino = true;
		}

		mElapsedTime -= 1000;
	}
}

void Grid::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mGridRect, states);
	for (const Tetromino::Ptr& t : mTetrominos)
		target.draw(*t, states);
}
