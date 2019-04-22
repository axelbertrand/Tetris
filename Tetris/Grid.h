#pragma once

#include "SceneNode.h"
#include "Tetromino.h"

class Grid : public SceneNode
{
	public :
		Grid();
		virtual ~Grid();

		void setSquareScale(float scale);
		void addTetromino(Tetromino::Ptr tetromino);
		bool needNewTetromino() const;
		virtual sf::FloatRect getBoundingRect() const;
		Tetromino* getCurrentTetromino() const;

	private :
		virtual void updateCurrent(sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void adaptTetrominoPosition();

		sf::RectangleShape mGridRect;
		Tetromino* mCurrentTetromino;

		int mElapsedTime;
		bool mNeedNewTetromino;
};

