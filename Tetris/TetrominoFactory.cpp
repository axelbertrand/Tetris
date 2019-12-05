#include "TetrominoFactory.h"

#include <random>
#include <chrono>

Tetromino TetrominoFactory::createTetromino(Tetromino::Type type)
{
	switch (type)
	{
		case Tetromino::Type::I :
			// XXXX
			return Tetromino(0b1111000000000000,  sf::Color::Cyan);

		case Tetromino::Type::J :
			// XXX
			//   X
			return Tetromino(0b1110001000000000, sf::Color::Blue);

		case Tetromino::Type::L :
			// XXX
			// X
			return Tetromino(0b1110100000000000, sf::Color(255, 153, 0)); // Orange

		case Tetromino::Type::O :
			// XX
			// XX
			return Tetromino(0b1100110000000000, sf::Color::Yellow);

		case Tetromino::Type::S :
			//  XX
			// XX
			return Tetromino(0b0110110000000000, sf::Color::Green);

		case Tetromino::Type::T :
			// XXX
			//  X
			return Tetromino(0b1110010000000000, sf::Color(204, 102, 255)); // Purple

		case Tetromino::Type::Z :
			// XX
			//  XX
			return Tetromino(0b1100011000000000, sf::Color::Red);
	}
}

Tetromino::Type TetrominoFactory::getRandomTetrominoType()
{
	std::default_random_engine randomEngine(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> distribution(0, 6);

	Tetromino::Type tetrominoType;
	switch (distribution(randomEngine))
	{
	case 0:
		tetrominoType = Tetromino::Type::I;
		break;
	case 1:
		tetrominoType = Tetromino::Type::J;
		break;
	case 2:
		tetrominoType = Tetromino::Type::L;
		break;
	case 3:
		tetrominoType = Tetromino::Type::O;
		break;
	case 4:
		tetrominoType = Tetromino::Type::S;
		break;
	case 5:
		tetrominoType = Tetromino::Type::T;
		break;
	case 6:
		tetrominoType = Tetromino::Type::Z;
		break;
	}

	return tetrominoType;
}
