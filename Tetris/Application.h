#pragma once

#include "Defs.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "StateStack.h"

class Application
{
	public :
		Application();
		~Application();

		void run();

	private :
		void processInput();
		void update(sf::Time dt);
		void render();
		void registerStates();
		void updateFps(sf::Time dt);

		static const sf::Time TIME_PER_FRAME;

		sf::RenderWindow mWindow;
		TextureHolder mTextures;
		FontHolder mFonts;
		StateStack mStateStack;

		sf::Text mFpsText;
		sf::Time mFpsUpdateTime;
		int mFpsNumFrames;
};
