#pragma once

#include "GameLib.h"
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
	void buildScene();
	void createTetromino();

	const unsigned int SCORE_MULTIPLIER{ 100 };
	const unsigned int LEVEL_UP_SCORE{ 400 };

	sf::RenderWindow& mWindow;
	TextureHolder& mTextures;
	FontHolder& mFonts;

	SceneNode mSceneGraph;
	std::queue<Command> mCommandQueue;

	unsigned int mTotalScore{ 0 };
	unsigned int mScoreSinceLastLevel{ 0 };
	unsigned int mLevel{ 1 };
	unsigned int mLinesNumber{ 0 };
	bool mIsGameFinished{ false };

	TextNode* mScoreDisplay;
	TextNode* mLevelDisplay;
	TextNode* mLinesNumberDisplay;
	Grid* mTetrisGrid;

	TetrominoFactory mTetrominoFactory;
};