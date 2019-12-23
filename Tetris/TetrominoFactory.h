#pragma once

#include "Tetromino.h"

class TetrominoFactory
{
public:
	std::unique_ptr<Tetromino> createRandomTetromino();

private:
	Tetromino::Type getRandomTetrominoType();
};

