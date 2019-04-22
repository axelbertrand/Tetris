#pragma once

enum class Category
{
	None = 0,
	Scene = 1 << 0,
	CurrentTetromino = 1 << 1,
	PlacedTetromino = 1 << 2,
};