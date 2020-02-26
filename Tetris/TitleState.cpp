#include "TitleState.h"

#include "ResourceHolder.h"
#include "Button.h"

TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
	sf::Vector2u windowSize = context.window->getSize();

	mTetrisTitle.setFont(context.fonts->get(FontsID::Title));
	mTetrisTitle.setString("TETRIS");
	mTetrisTitle.setCharacterSize(120u);
	mTetrisTitle.setPosition((windowSize.x - mTetrisTitle.getLocalBounds().width) / 2, 10);
	mTetrisTitle.setFillColor(sf::Color::Black);

	auto newGameButton = std::make_shared<gui::Button>(context);
	newGameButton->setPosition(300, 200);
	newGameButton->setText("Nouvelle partie");
	newGameButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(StatesID::Game);
	});

	auto loadGameButton = std::make_shared<gui::Button>(context);
	loadGameButton->setPosition(300, 300);
	loadGameButton->setText("Charger partie");
	loadGameButton->setCallback([this]()
	{
		requestStackPop();
		requestStackPush(StatesID::LoadingGame);
	});

	auto settingsButton = std::make_shared<gui::Button>(context);
	settingsButton->setPosition(300, 400);
	settingsButton->setText("Options");
	settingsButton->setCallback([this]()
	{
		requestStackPush(StatesID::Settings);
	});

	auto quitButton = std::make_shared<gui::Button>(context);
	quitButton->setPosition(300, 500);
	quitButton->setText("Quitter");
	quitButton->setCallback([this]()
	{
		requestStackPop();
	});

	mContainer.pack(newGameButton);
	mContainer.pack(loadGameButton);
	mContainer.pack(settingsButton);
	mContainer.pack(quitButton);
}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mTetrisTitle);
	window.draw(mContainer);
}

bool TitleState::update(sf::Time dt)
{
	return true;
}

bool TitleState::handleEvent(const sf::Event & event)
{
	mContainer.handleEvent(event);
	return false;
}
