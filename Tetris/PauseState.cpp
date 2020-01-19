#include "PauseState.h"

#include "Button.h"
#include "StateStack.h"

PauseState::PauseState(StateStack& stack, Context context, bool letUpdateThrough)
	: State(stack, context)
	, mLetUpdateThrough(letUpdateThrough)
{
	sf::Font& font = context.fonts->get(FontsID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	mPauseText.setFont(font);
	mPauseText.setString("Game Paused");
	mPauseText.setCharacterSize(50);

	sf::FloatRect bounds = mPauseText.getLocalBounds();
	mPauseText.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	mPauseText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);

	auto resumeGameButton = std::make_shared<gui::Button>(*context.fonts, *context.textures);
	resumeGameButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 75);
	resumeGameButton->setText("Resume game");
	resumeGameButton->setCallback([this]()
	{
		requestStackPop();
	});

	auto backToMenuButton = std::make_shared<gui::Button>(*context.fonts, *context.textures);
	backToMenuButton->setPosition(0.5f * windowSize.x - 100, 0.4f * windowSize.y + 125);
	backToMenuButton->setText("Back to menu");
	backToMenuButton->setCallback([this]()
	{
		mStack->save();
		requestStateClear();
		requestStackPush(StatesID::Title);
	});

	mContainer.pack(resumeGameButton);
	mContainer.pack(backToMenuButton);
}

void PauseState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	// Darken the screen with semi-transparent black rectangle
	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPauseText);
	window.draw(mContainer);
}

bool PauseState::update(sf::Time dt)
{
	return mLetUpdateThrough;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	mContainer.handleEvent(event);

	// Press Escape key to resume the game
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPop();
	}

	return false;
}
