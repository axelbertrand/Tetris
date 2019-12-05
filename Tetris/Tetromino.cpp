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
