#pragma once

#include "SceneNode.h"
#include "Tetromino.h"

class Grid : public SceneNode
{
	public :
		Grid();
		virtual ~Grid();

		void setSquareScale(float scale);
		void add(Tetromino::Ptr tetromino);
		bool needNewTetromino() const;

	private :
		virtual void updateCurrent(sf::Time dt);
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

		sf::RectangleShape mGridRect;
		std::vector<Tetromino::Ptr> mTetrominos;
		int mCurrentTetromino;

		int mElapsedTime;
		bool mNeedNewTetromino;
};

