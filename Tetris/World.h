#pragma once

#include "Defs.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"

#include <array>
#include <queue>

class World : private sf::NonCopyable
{
	public:
		explicit World(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);
		void update(sf::Time dt);
		void draw();


	private:
		void loadTextures();
		void buildScene();

		sf::RenderWindow& mWindow;
		TextureHolder& mTextures;
		FontHolder& mFonts;

		SceneNode mSceneGraph;

		int mScore;
		int mLevel;
		int mLinesNumber;
};