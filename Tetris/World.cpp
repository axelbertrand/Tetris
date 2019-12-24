#include "World.h"

#include "SpriteNode.h"

#include <memory>
#include <algorithm>
#include <cmath>


World::World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts)
	: mWindow(window)
	, mTextures(textures)
	, mFonts(fonts)
{
	loadTextures();
	buildScene();
}

void World::update(sf::Time dt)
{
	mScoreDisplay->setString(std::to_string(mTotalScore));
	mLevelDisplay->setString(std::to_string(mLevel));
	mLinesNumberDisplay->setString(std::to_string(mLinesNumber));

	if (mTetrisGrid->needNewTetromino())
	{
		if (unsigned int completedLinesCount = mTetrisGrid->getCompletedLinesCount(); completedLinesCount > 0)
		{
			mScoreSinceLastLevel += completedLinesCount * SCORE_MULTIPLIER;
			mTotalScore += completedLinesCount * SCORE_MULTIPLIER;
			double levelUpCeil = STARTING_LEVEL_UP_SCORE * (1 + (mLevel - 1) / 10.);
			if (mScoreSinceLastLevel >= levelUpCeil)
			{
				++mLevel;
				mScoreSinceLastLevel -= static_cast<unsigned int>(levelUpCeil);
				mTetrisGrid->increaseSpeed();
			}
		}

		std::unique_ptr<Tetromino> nextTetromino = mTetrominoFactory.createRandomTetromino();
		if (!mTetrisGrid->addTetromino(std::move(nextTetromino)))
		{
			mIsGameFinished = true;
		}
	}

	while (!mCommandQueue.empty())
	{
		mSceneGraph.onCommand(mCommandQueue.back(), dt);
		mCommandQueue.pop();
	}

	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.draw(mSceneGraph);
}

std::queue<Command>& World::getCommandQueue()
{
	return mCommandQueue;
}

void World::loadTextures()
{

}

void World::buildScene()
{
	std::unique_ptr<TextNode> tetrisText = std::make_unique<TextNode>("TETRIS", mFonts);
	tetrisText->setPosition(static_cast<float>(mWindow.getSize().x / 2), 50);

	std::unique_ptr<Grid> tetrisGrid = std::make_unique<Grid>();
	tetrisGrid->setPosition(0, 50);
	mTetrisGrid = tetrisGrid.get();

	tetrisText->attachChild(std::move(tetrisGrid));
	mSceneGraph.attachChild(std::move(tetrisText));

	std::unique_ptr<TextNode> holdPieceText = std::make_unique<TextNode>("Conservée", mFonts);
	holdPieceText->setPosition(100, 100);
	mSceneGraph.attachChild(std::move(holdPieceText));

	std::unique_ptr<TextNode> nextPieceText = std::make_unique<TextNode>("Suivante", mFonts);
	nextPieceText->setPosition(static_cast<float>(mWindow.getSize().x - 100), 100);
	mSceneGraph.attachChild(std::move(nextPieceText));


	std::unique_ptr<TextNode> scoreTitleText = std::make_unique<TextNode>("Score", mFonts);
	scoreTitleText->setPosition(100, 300);

	std::unique_ptr<TextNode> scoreText = std::make_unique<TextNode>(std::to_string(mTotalScore), mFonts);
	scoreText->setPosition(0, 50);
	mScoreDisplay = scoreText.get();

	scoreTitleText->attachChild(std::move(scoreText));
	mSceneGraph.attachChild(std::move(scoreTitleText));


	std::unique_ptr<TextNode> levelTitleText = std::make_unique<TextNode>("Niveau", mFonts);
	levelTitleText->setPosition(100, 400);

	std::unique_ptr<TextNode> levelText = std::make_unique<TextNode>(std::to_string(mLevel), mFonts);
	levelText->setPosition(0, 50);
	mLevelDisplay = levelText.get();

	levelTitleText->attachChild(std::move(levelText));
	mSceneGraph.attachChild(std::move(levelTitleText));


	std::unique_ptr<TextNode> linesNumberTitleText = std::make_unique<TextNode>("Lignes", mFonts);
	linesNumberTitleText->setPosition(100, 500);

	std::unique_ptr<TextNode> linesNumberText = std::make_unique<TextNode>(std::to_string(mLinesNumber), mFonts);
	linesNumberText->setPosition(0, 50);
	mLinesNumberDisplay = linesNumberText.get();

	linesNumberTitleText->attachChild(std::move(linesNumberText));
	mSceneGraph.attachChild(std::move(linesNumberTitleText));


	createTetromino();
}

void World::createTetromino()
{
	mTetrisGrid->addTetromino(mTetrominoFactory.createRandomTetromino());
}
