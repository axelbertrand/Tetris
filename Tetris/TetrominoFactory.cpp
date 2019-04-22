#include "TetrominoFactory.h"

Tetromino* TetrominoFactory::createTetromino(Tetromino::Type type)
{
	switch (type)
	{
		case Tetromino::Type::I :
				return new Tetromino({
					sf::Vector2f(0.f, 0.f), sf::Vector2f(4.f, 0.f), sf::Vector2f(4.f, 1.f), sf::Vector2f(0.f, 1.f)
				},  sf::Color::Cyan);

		case Tetromino::Type::J :
				return new Tetromino({
					sf::Vector2f(3.f, 0.f), sf::Vector2f(3.f, 2.f), sf::Vector2f(2.f, 2.f), sf::Vector2f(2.f, 1.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(0.f, 0.f)
				}, sf::Color::Blue);

		case Tetromino::Type::L :
				return new Tetromino({
					sf::Vector2f(0.f, 0.f), sf::Vector2f(3.f, 0.f), sf::Vector2f(3.f, 1.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 2.f), sf::Vector2f(0.f, 2.f)
				}, sf::Color(255, 153, 0)); // Orange

		case Tetromino::Type::O :
				return new Tetromino({
					sf::Vector2f(0.f, 0.f), sf::Vector2f(2.f, 0.f), sf::Vector2f(2.f, 2.f), sf::Vector2f(0.f, 2.f)
				}, sf::Color::Yellow);

		case Tetromino::Type::S :
			return new Tetromino({
				sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), sf::Vector2f(3.f, 0.f), sf::Vector2f(3.f, 1.f), sf::Vector2f(2.f, 1.f), sf::Vector2f(2.f, 2.f), sf::Vector2f(0.f, 2.f), sf::Vector2f(0.f, 1.f)
			}, sf::Color::Green);

		case Tetromino::Type::T :
			return new Tetromino({
				sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(3.f, 0.f), sf::Vector2f(3.f, 1.f), sf::Vector2f(2.f, 1.f), sf::Vector2f(2.f, 2.f), sf::Vector2f(1.f, 2.f)
			}, sf::Color(204, 102, 255)); // Purple

		case Tetromino::Type::Z :
			return new Tetromino({
				sf::Vector2f(2.f, 1.f), sf::Vector2f(3.f, 1.f), sf::Vector2f(3.f, 2.f), sf::Vector2f(1.f, 2.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(2.f, 0.f)
			}, sf::Color::Red);
	}

	return nullptr;
}
