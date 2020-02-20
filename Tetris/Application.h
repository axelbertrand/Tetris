#pragma once

#include "GameLib.h"
#include "ResourceHolder.h"
#include "StateStack.h"

class Application
{
	public:
		Application();

		void run();

	private:
		void processInput();
		void update(sf::Time dt);
		void render();
		void registerStates();
		void updateFps(sf::Time dt);

		static const sf::Time TIME_PER_FRAME;

		sf::RenderWindow mWindow{ sf::VideoMode(800u, 600u), "Tetris" };
		TextureHolder mTextures;
		FontHolder mFonts;

		KeyBinding mKeyBinding;
		StateStack mStateStack{ State::Context(mWindow, mTextures, mFonts, mKeyBinding) };

		sf::Sprite mBackground;

		sf::Text mFpsText;
		sf::Time mFpsUpdateTime;
		int mFpsNumFrames{ 0 };
};
