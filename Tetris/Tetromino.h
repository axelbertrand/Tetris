#pragma once

#include "Defs.h"
#include "SceneNode.h"
#include <memory>

class Tetromino : public SceneNode
{
	public :
		typedef std::unique_ptr<Tetromino> Ptr;

		enum class Type
		{
			I, J, L, O, S, T, Z
		};

		static Type getRandomType();

		Tetromino(std::vector<sf::Vector2f> shapePoints, sf::Color color);
		virtual ~Tetromino();

		virtual sf::FloatRect getBoundingRect() const;

		virtual Category getCategory() const;

		void setPlaced(bool placed);

	private :
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::VertexArray mVertexArray;
		bool mIsPlaced;
};

