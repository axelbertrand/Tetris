#pragma once

#include "Defs.h"
#include "SceneNode.h"
#include <bitset>

class Tetromino
{
	public:
		enum class Type
		{
			I, J, L, O, S, T, Z
		};

		Tetromino(uint16_t shape, sf::Color color);
		Tetromino(const Tetromino& other) = delete;
		virtual ~Tetromino();

		std::bitset<16> getShape() const;
		sf::Color getColor() const;
		unsigned int getValue() const;

	private:
		std::bitset<16> mShape;
		sf::Color mColor;
		unsigned int mValue;

		static unsigned int sMaxValue;
};

