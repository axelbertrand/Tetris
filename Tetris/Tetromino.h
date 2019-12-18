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

		Tetromino(uint16_t shape, std::size_t maxSize, sf::Color color, Type type);
		Tetromino(const Tetromino& other) = delete;
		virtual ~Tetromino();

		void rotate(bool clockWise = true);
		void forEachTile(std::function<void(std::size_t, std::size_t)> callback);

		std::bitset<16> getShape() const;
		std::size_t getMaxSize() const;
		sf::Color getColor() const;
		Type getType() const;
		unsigned int getRotationState() const;
		unsigned int getValue() const;

	private:
		std::bitset<16> mShape;
		std::size_t mMaxSize;
		sf::Color mColor;
		Type mType;
		unsigned int mRotationState;
		unsigned int mValue;

		static unsigned int sMaxValue;
};

