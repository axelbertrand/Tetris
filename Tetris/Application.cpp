#include "Application.h"
#include <sstream>

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

Application::Application() :
mWindow(sf::VideoMode(800u, 600u), "Tetris"),
mFonts(),
mText()
{
	mWindow.setKeyRepeatEnabled(false);

	mFonts.load(Fonts::Main, "arial.ttf");

	mText.setFont(mFonts.get(Fonts::Main));
	mText.setPosition(5.f, 5.f);
	mText.setCharacterSize(10u);
	mText.setFillColor(sf::Color::Black);
	mText.setString("texte");
}

Application::~Application()
{
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate(sf::Time::Zero);

	while (mWindow.isOpen())
	{
		sf::Time elapsedTime(clock.restart());
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			processEvents();
		}

		render();
	}
}

void Application::processEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow.close();
				break;
		}
	}
}

void Application::render()
{
	mWindow.clear(sf::Color::White);

	mWindow.draw(mText);

	mWindow.display();
}