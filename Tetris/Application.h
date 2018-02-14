#pragma once

#include "Defs.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

class Application
{
	public:
		Application();
		~Application();

		void run();

	private:
		void processEvents();
		void render();

		static const sf::Time TIME_PER_FRAME;

		sf::RenderWindow mWindow;
		FontHolder mFonts;
		sf::Text mText;
};
