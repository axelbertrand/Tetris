#pragma once

#include "Defs.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "TextNode.h"
#include "Grid.h"

#include "TetrominoFactory.h"

class World : private sf::NonCopyable
{
	public:
		explicit World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);
		void update(sf::Time dt);
		void draw();


	private:
		void loadTextures();
		void buildScene();
		void createTetromino();

		sf::RenderWindow& mWindow;
		TextureHolder& mTextures;
		FontHolder& mFonts;

		SceneNode mSceneGraph;

		int mScore;
		int mLevel;
		int mLinesNumber;

		TextNode* mScoreDisplay;
		TextNode* mLevelDisplay;
		TextNode* mLinesNumberDisplay;
		Grid* mTetrisGrid;

		TetrominoFactory mTetrominoFactory;
};