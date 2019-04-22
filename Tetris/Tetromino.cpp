#include "Tetromino.h"

#include <random>
#include <chrono>

Tetromino::Tetromino(std::vector<sf::Vector2f> shapePoints, sf::Color color) :
mVertexArray(sf::PrimitiveType::TriangleFan),
mIsPlaced(false)
{
	for(sf::Vector2f point : shapePoints)
		mVertexArray.append(sf::Vertex(point, color));

	sf::FloatRect bounds = mVertexArray.getBounds();
	setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
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

sf::FloatRect Tetromino::getBoundingRect() const
{
	return getWorldTransform().transformRect(mVertexArray.getBounds());
}

Category Tetromino::getCategory() const
{
	return mIsPlaced ? Category::PlacedTetromino : Category::CurrentTetromino;
}

void Tetromino::setPlaced(bool placed)
{
	mIsPlaced = placed;
}

void Tetromino::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mVertexArray, states);
}
