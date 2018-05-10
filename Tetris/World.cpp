#include "World.h"

#include "SpriteNode.h"

#include <algorithm>
#include <cmath>


World::World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts) :
mWindow(window),
mTextures(textures),
mFonts(fonts),
mSceneGraph(),
mScore(0),
mLevel(1),
mLinesNumber(0)
{
	loadTextures();
	buildScene();
}

void World::update(sf::Time dt)
{
	mScoreDisplay->setString(std::to_string(mScore));
	mLevelDisplay->setString(std::to_string(mLevel));
	mLinesNumberDisplay->setString(std::to_string(mLinesNumber));

	if (mTetrisGrid->needNewTetromino())
	{
		createTetromino();
	}

	mSceneGraph.update(dt);
}

void World::draw()
{
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{

}

void World::buildScene()
{
	std::unique_ptr<TextNode> tetrisText = std::make_unique<TextNode>("TETRIS", mFonts);
	tetrisText->setPosition(static_cast<float>(mWindow.getSize().x / 2), 50);

	std::unique_ptr<Grid> tetrisGrid = std::make_unique<Grid>();
	tetrisGrid->setPosition(0, 275);
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

	std::unique_ptr<TextNode> scoreText = std::make_unique<TextNode>(std::to_string(mScore), mFonts);
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
	Tetromino::Ptr t(mTetrominoFactory.createTetromino(Tetromino::getRandomType()));
	mTetrisGrid->add(t);
}
