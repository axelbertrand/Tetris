#include "Tetromino.h"

unsigned int Tetromino::sMaxValue = 0;

Tetromino::Tetromino(uint16_t shape, std::size_t maxSize, sf::Color color)
	: mShape(shape)
	, mMaxSize(maxSize)
	, mColor(color)
	, mRotationState(0)
	, mValue(++sMaxValue)
{
}

Tetromino::~Tetromino()
{
}

void Tetromino::rotate(bool clockWise)
{
	std::bitset<16> newShape;
	std::size_t ni = 0, nj = 0;
	std::size_t i, j;
	if (clockWise)
	{
		for (j = 0; j < mMaxSize; ++j)
		{
			nj = 0;
			for (i = mMaxSize - 1; i != static_cast<std::size_t>(-1); --i)
			{
				newShape[ni * mMaxSize + nj] = mShape[i * mMaxSize + j];
				nj++;
			}
			++ni;
		}
		mRotationState = (mRotationState + 1) % 4;
	}
	else
	{
		for (j = mMaxSize - 1; j != static_cast<std::size_t>(-1); --j)
		{
			nj = 0;
			for (i = 0; i < mMaxSize; ++i)
			{
				newShape[ni * mMaxSize + nj] = mShape[i * mMaxSize + j];
				nj++;
			}
			++ni;
		}
		mRotationState = (mRotationState - 1) % 4;
	}

	mShape = newShape;
}

void Tetromino::forEachTile(std::function<void(std::size_t, std::size_t)> callback)
{
	for (std::size_t i = 0; i < mMaxSize; ++i)
	{
		for (std::size_t j = 0; j < mMaxSize; ++j)
		{
			if (mShape.test(i * mMaxSize + j))
			{
				callback(i, j);
			}
		}
	}
}

std::bitset<16> Tetromino::getShape() const
{
	return mShape;
}

std::size_t Tetromino::getMaxSize() const
{
	return mMaxSize;
}

sf::Color Tetromino::getColor() const
{
	return mColor;
}

unsigned int Tetromino::getRotationState() const
{
	return mRotationState;
}

unsigned int Tetromino::getValue() const
{
	return mValue;
}
