#pragma once

#include "Defs.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "TextNode.h"
#include "Grid.h"
#include "Command.h"
#include <queue>

#include "TetrominoFactory.h"

class World : private sf::NonCopyable
{
	public:
		explicit World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);
		void update(sf::Time dt);
		void draw();

		std::queue<Command>& getCommandQueue();

	private:
		void loadTextures();
		void adaptTetrominoPosition();
		void buildScene();
		void createTetromino();
		sf::FloatRect getGridBounds() const;

		sf::RenderWindow& mWindow;
		TextureHolder& mTextures;
		FontHolder& mFonts;

		SceneNode mSceneGraph;
		std::queue<Command> mCommandQueue;

		int mScore;
		int mLevel;
		int mLinesNumber;

		TextNode* mScoreDisplay;
		TextNode* mLevelDisplay;
		TextNode* mLinesNumberDisplay;
		Grid* mTetrisGrid;

		TetrominoFactory mTetrominoFactory;
};