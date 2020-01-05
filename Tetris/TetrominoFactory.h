#pragma once

#include <random>
#include <chrono>
#include "Tetromino.h"

class TetrominoFactory
{
public:
	std::unique_ptr<Tetromino> createRandomTetromino();

private:
	Tetromino::Type getRandomTetrominoType();

	std::default_random_engine mRandomGenerator{ std::chrono::system_clock::now().time_since_epoch().count() };
};

