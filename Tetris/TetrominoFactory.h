#pragma once

#include "Tetromino.h"

class TetrominoFactory
{
	public:
		Tetromino createTetromino(Tetromino::Type type);

	private:
		Tetromino::Type getRandomTetrominoType();
};

