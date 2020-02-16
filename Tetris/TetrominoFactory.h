#pragma once

#include <random>
#include <chrono>
#include "Tetromino.h"

class TetrominoFactory
{
public:
	TetrominoFactory(const TetrominoFactory&) = delete;
	TetrominoFactory& operator=(const TetrominoFactory&) = delete;
	TetrominoFactory(TetrominoFactory&&) = delete;
	TetrominoFactory& operator=(TetrominoFactory&&) = delete;

	static TetrominoFactory& getInstance() {
		static TetrominoFactory s_instance;
		return s_instance;
	}

	std::unique_ptr<Tetromino> createTetromino(Tetromino::Type tetrominoType) const;
	std::unique_ptr<Tetromino> createRandomTetromino();

private:
	TetrominoFactory() = default;
	Tetromino::Type getRandomTetrominoType();

	std::default_random_engine mRandomGenerator{ std::chrono::system_clock::now().time_since_epoch().count() };
};

