#include "Application.h"

#include "ResourceIdentifiers.h"
#include "State.h"
#include "TitleState.h"
#include "GameState.h"
#include "MenuState.h"
#include "SettingState.h"
#include "LoadingGameState.h"

const sf::Time Application::TIME_PER_FRAME = sf::seconds(1.f / 60.f);

Application::Application()
{
	mFonts.load(FontsID::Main, "PressStart2P.ttf");
	mFonts.load(FontsID::Title, "Games.ttf");

	mTextures.load(TexturesID::BackGround, "background.png");
	mTextures.load(TexturesID::ButtonNormal, "ButtonNormal.png");
	mTextures.load(TexturesID::ButtonSelected, "ButtonSelected.png");
	mTextures.load(TexturesID::ButtonPressed, "ButtonPressed.png");

	mBackground.setTexture(mTextures.get(TexturesID::BackGround));

	mFpsText.setFont(mFonts.get(FontsID::Main));
	mFpsText.setCharacterSize(10u);
	mFpsText.setPosition(5.f, 5.f);

	registerStates();
	mStateStack.pushState(StatesID::Title);
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

			processInput();
			update(TIME_PER_FRAME);

			if (mStateStack.isEmpty())
				mWindow.close();
		}

		updateFps(elapsedTime);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		mStateStack.handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}

void Application::update(sf::Time dt)
{
	mStateStack.update(dt);
}

void Application::render()
{
	mWindow.clear(sf::Color::White);

	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mBackground);
	mWindow.draw(mFpsText);

	mStateStack.draw();

	mWindow.display();
}

void Application::registerStates()
{
	mStateStack.registerState<TitleState>(StatesID::Title);
	mStateStack.registerState<GameState>(StatesID::Game);
	mStateStack.registerState<MenuState>(StatesID::Menu);
	mStateStack.registerState<SettingState>(StatesID::Settings);
	mStateStack.registerState<LoadingGameState>(StatesID::LoadingGame);
}

void Application::updateFps(sf::Time dt)
{
	mFpsUpdateTime += dt;
	mFpsNumFrames += 1;
	if (mFpsUpdateTime >= sf::seconds(1.0f))
	{
		mFpsText.setString(std::to_string(mFpsNumFrames) + " FPS");

		mFpsUpdateTime -= sf::seconds(1.0f);
		mFpsNumFrames = 0;
	}
}
