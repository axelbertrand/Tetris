#include "TitleState.h"

#include "ResourceHolder.h"

TitleState::TitleState(StateStack& stack, Context context) :
State(stack, context),
mTetrisTitle(),
mNewGameButton(),
mLoadGameButton(),
mSettingsButton(),
mQuitButton()
{
	sf::Vector2u windowSize = context.window->getSize();

	mTetrisTitle.setFont(context.fonts->get(Fonts::Title));
	mTetrisTitle.setString("TETRIS");
	mTetrisTitle.setCharacterSize(120u);
	mTetrisTitle.setPosition((windowSize.x - mTetrisTitle.getLocalBounds().width) / 2, 10);
	mTetrisTitle.setFillColor(sf::Color::Black);

	mNewGameButton.setFont(context.fonts->get(Fonts::Main));
	mNewGameButton.setString("Nouvelle partie");
	mNewGameButton.setCharacterSize(20u);
	mNewGameButton.setPosition((windowSize.x - mNewGameButton.getLocalBounds().width) / 2, 200);
	mNewGameButton.setFillColor(sf::Color::Black);

	mLoadGameButton.setFont(context.fonts->get(Fonts::Main));
	mLoadGameButton.setString("Charger partie");
	mLoadGameButton.setCharacterSize(20u);
	mLoadGameButton.setPosition((windowSize.x - mLoadGameButton.getLocalBounds().width) / 2, 300);
	mLoadGameButton.setFillColor(sf::Color::Black);

	mSettingsButton.setFont(context.fonts->get(Fonts::Main));
	mSettingsButton.setString("Options");
	mSettingsButton.setCharacterSize(20u);
	mSettingsButton.setPosition((windowSize.x - mSettingsButton.getLocalBounds().width) / 2, 400);
	mSettingsButton.setFillColor(sf::Color::Black);

	mQuitButton.setFont(context.fonts->get(Fonts::Main));
	mQuitButton.setString("Quitter");
	mQuitButton.setCharacterSize(20u);
	mQuitButton.setPosition((windowSize.x - mQuitButton.getLocalBounds().width) / 2, 500);
	mQuitButton.setFillColor(sf::Color::Black);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mTetrisTitle);
	window.draw(mNewGameButton);
	window.draw(mLoadGameButton);
	window.draw(mSettingsButton);
	window.draw(mQuitButton);
}

bool TitleState::update(sf::Time dt)
{
	return false;
}

bool TitleState::handleEvent(const sf::Event & event)
{
	return false;
}
