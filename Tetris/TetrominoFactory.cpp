#include "TetrominoFactory.h"

#include <random>
#include <chrono>

std::unique_ptr<Tetromino> TetrominoFactory::createRandomTetromino()
{
	switch (getRandomTetrominoType())
	{
		case Tetromino::Type::I :
			// XXXX
			return std::make_unique<Tetromino>(0b0000000000001111,  sf::Color::Cyan);

		case Tetromino::Type::J :
			// XXX
			//   X
			return std::make_unique<Tetromino>(0b0000000001000111, sf::Color::Blue);

		case Tetromino::Type::L :
			// XXX
			// X
			return std::make_unique<Tetromino>(0b0000000000010111, sf::Color(255, 153, 0)); // Orange

		case Tetromino::Type::O :
			// XX
			// XX
			return std::make_unique<Tetromino>(0b0000000000110011, sf::Color::Yellow);

		case Tetromino::Type::S :
			//  XX
			// XX
			return std::make_unique<Tetromino>(0b0000000000110110, sf::Color::Green);

		case Tetromino::Type::T :
			// XXX
			//  X
			return std::make_unique<Tetromino>(0b0000000000100111, sf::Color(204, 102, 255)); // Purple

		case Tetromino::Type::Z :
			// XX
			//  XX
			return std::make_unique<Tetromino>(0b0000000001100011, sf::Color::Red);
	}
}

Tetromino::Type TetrominoFactory::getRandomTetrominoType()
{
	std::default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution(0, 6);

	switch (distribution(randomEngine))
	{
	case 0:
		return Tetromino::Type::I;
	case 1:
		return Tetromino::Type::J;
	case 2:
		return Tetromino::Type::L;
	case 3:
		return Tetromino::Type::O;
	case 4:
		return Tetromino::Type::S;
	case 5:
		return Tetromino::Type::T;
	case 6:
	default:
		return Tetromino::Type::Z;
	}
}
