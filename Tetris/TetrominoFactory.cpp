#include "TetrominoFactory.h"

std::unique_ptr<Tetromino> TetrominoFactory::createRandomTetromino()
{
	switch (getRandomTetrominoType())
	{
	case Tetromino::Type::I :
		// XXXX
		return std::make_unique<Tetromino>(0b0000000011110000, 4,  sf::Color::Cyan, Tetromino::Type::I);

	case Tetromino::Type::J :
		// X
		// XXX
		return std::make_unique<Tetromino>(0b0000000000111001, 3, sf::Color::Blue, Tetromino::Type::J);

	case Tetromino::Type::L :
		//   X
		// XXX
		return std::make_unique<Tetromino>(0b0000000000111100, 3, sf::Color(255, 153, 0), Tetromino::Type::L); // Orange

	case Tetromino::Type::O :
		// XX
		// XX
		return std::make_unique<Tetromino>(0b00000000001111, 2, sf::Color::Yellow, Tetromino::Type::O);

	case Tetromino::Type::S :
		//  XX
		// XX
		return std::make_unique<Tetromino>(0b0000000000011110, 3, sf::Color::Green, Tetromino::Type::S);

	case Tetromino::Type::T :
		//  X
		// XXX
		return std::make_unique<Tetromino>(0b0000000000111010, 3, sf::Color(204, 102, 255), Tetromino::Type::T); // Purple

	case Tetromino::Type::Z :
		// XX
		//  XX
		return std::make_unique<Tetromino>(0b0000000000110011, 3, sf::Color::Red, Tetromino::Type::Z);
	}

	return nullptr;
}

Tetromino::Type TetrominoFactory::getRandomTetrominoType()
{
	std::uniform_int_distribution<int> distribution(0, 6);

	switch (distribution(mRandomGenerator))
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
		[[fallthrough]];
	default:
		return Tetromino::Type::Z;
	}
}
