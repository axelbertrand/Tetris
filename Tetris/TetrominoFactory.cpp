#include "TetrominoFactory.h"

Tetromino* TetrominoFactory::createTetromino(Tetromino::Type type)
{
	switch (type)
	{
		case Tetromino::Type::I :
				return new Tetromino({
					true, true, true, true
				}, 4, 1, sf::Color::Cyan);

		case Tetromino::Type::J :
				return new Tetromino({
					true, true, true,
					false, false, true
				}, 3, 2, sf::Color::Blue);

		case Tetromino::Type::L :
				return new Tetromino({
					true, true, true,
					true, false, false
				}, 3, 2, sf::Color(255, 153, 0)); // Orange

		case Tetromino::Type::O :
				return new Tetromino({
					true, true,
					true, true
				}, 2, 2, sf::Color::Yellow);

		case Tetromino::Type::S :
			return new Tetromino({
				false, true, true,
				true, true, false
			}, 3, 2, sf::Color::Green);

		case Tetromino::Type::T :
			return new Tetromino({
				true, true, true,
				false, true, false
			}, 3, 2, sf::Color(204, 102, 255)); // Purple

		case Tetromino::Type::Z :
			return new Tetromino({
				true, true, false,
				false, true, true
			}, 3, 2, sf::Color::Red);
	}
}
