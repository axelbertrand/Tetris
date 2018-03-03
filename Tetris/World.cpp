#include "World.h"

#include "SpriteNode.h"
#include "TextNode.h"

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
	std::unique_ptr<TextNode> tetrisText(new TextNode("TETRIS", mFonts));
	tetrisText->setPosition(static_cast<float>(mWindow.getSize().x / 2), 50);
	mSceneGraph.attachChild(std::move(tetrisText));

	std::unique_ptr<TextNode> holdPieceText(new TextNode("Conservée", mFonts));
	holdPieceText->setPosition(100, 100);
	mSceneGraph.attachChild(std::move(holdPieceText));

	std::unique_ptr<TextNode> nextPieceText(new TextNode("Suivante", mFonts));
	nextPieceText->setPosition(static_cast<float>(mWindow.getSize().x - 100), 100);
	mSceneGraph.attachChild(std::move(nextPieceText));


	std::unique_ptr<TextNode> scoreTitleText(new TextNode("Score", mFonts));
	scoreTitleText->setPosition(100, 300);

	std::unique_ptr<TextNode> scoreText(new TextNode(std::to_string(mScore), mFonts));
	scoreText->setPosition(0, 50);
	scoreTitleText.get()->attachChild(std::move(scoreText));
	mSceneGraph.attachChild(std::move(scoreTitleText));


	std::unique_ptr<TextNode> levelTitleText(new TextNode("Niveau", mFonts));
	levelTitleText->setPosition(100, 400);

	std::unique_ptr<TextNode> levelText(new TextNode(std::to_string(mLevel), mFonts));
	levelText->setPosition(0, 50);
	levelTitleText.get()->attachChild(std::move(levelText));
	mSceneGraph.attachChild(std::move(levelTitleText));


	std::unique_ptr<TextNode> linesNumberTitleText(new TextNode("Lignes", mFonts));
	linesNumberTitleText->setPosition(100, 500);

	std::unique_ptr<TextNode> linesNumberText(new TextNode(std::to_string(mLinesNumber), mFonts));
	linesNumberText->setPosition(0, 50);
	linesNumberTitleText.get()->attachChild(std::move(linesNumberText));
	mSceneGraph.attachChild(std::move(linesNumberTitleText));
}