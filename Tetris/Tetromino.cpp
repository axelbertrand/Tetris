#include "Tetromino.h"

unsigned int Tetromino::sMaxValue = 0;

Tetromino::Tetromino(uint16_t shape, sf::Color color)
	: mShape(shape)
	, mColor(color)
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
		for (j = 0; j < 4; ++j) {
			nj = 0;
			for (i = 3; i > -1; --i) {
				newShape[ni * 4 + nj] = mShape[i * 4 + j];
				nj++;
			}
			++ni;
		}
	}
	else
	{
		for (j = 3; j > -1; --j) {
			nj = 0;
			for (i = 0; i < 4; ++i) {
				newShape[ni * 4 + nj] = mShape[i * 4 + j];
				nj++;
			}
			++ni;
		}
	}

	mShape = newShape;
}

std::bitset<16> Tetromino::getShape() const
{
	return mShape;
}

sf::Color Tetromino::getColor() const
{
	return mColor;
}

unsigned int Tetromino::getValue() const
{
	return mValue;
}
