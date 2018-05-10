#include "Tetromino.h"

#include <random>
#include <chrono>

Tetromino::Tetromino(std::vector<bool> shapeArray, int width, int height, sf::Color color) :
mVertexArray(sf::Quads),
mWidth(width),
mHeight(height),
mColor(color)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < width; ++j)
		{
			if (shapeArray[i*width + j])
			{
				mVertexArray.append(sf::Vertex(sf::Vector2f(0.f + j, 0.f + i), color));
				mVertexArray.append(sf::Vertex(sf::Vector2f(0.f + j, 1.f + i), color));
				mVertexArray.append(sf::Vertex(sf::Vector2f(1.f + j, 1.f + i), color));
				mVertexArray.append(sf::Vertex(sf::Vector2f(1.f + j, 0.f + i), color));
			}
		}
	}
}

Tetromino::~Tetromino()
{
}

Tetromino::Type Tetromino::getRandomType()
{
	std::default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution(0, 6);

	Type tetrominoType;
	switch (distribution(randomEngine))
	{
		case 0 :
			tetrominoType = Type::I;
			break;
		case 1:
			tetrominoType = Type::J;
			break;
		case 2:
			tetrominoType = Type::L;
			break;
		case 3:
			tetrominoType = Type::O;
			break;
		case 4:
			tetrominoType = Type::S;
			break;
		case 5:
			tetrominoType = Type::T;
			break;
		case 6:
			tetrominoType = Type::Z;
			break;
	}

	return tetrominoType;
}

sf::FloatRect Tetromino::getLocalBounds() const
{
	return sf::FloatRect(0.f, 0.f, mWidth, mHeight);
}

sf::FloatRect Tetromino::getGlobalBounds() const
{
	return sf::FloatRect(getPosition().x, getPosition().y, mWidth * getScale().x, mHeight * getScale().y);
}

void Tetromino::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	target.draw(mVertexArray, states);
}
