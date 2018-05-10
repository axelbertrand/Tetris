#pragma once

#include "Defs.h"
#include <memory>

class Tetromino : public sf::Transformable, public sf::Drawable
{
	public :
		typedef std::shared_ptr<Tetromino> Ptr;

		enum class Type
		{
			I, J, L, O, S, T, Z
		};

		Tetromino(std::vector<bool> shapeArray, int width, int height, sf::Color color);
		virtual ~Tetromino();

		static Type getRandomType();

		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;

	private :
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::VertexArray mVertexArray;
		int mWidth;
		int mHeight;
		sf::Color mColor;
};

