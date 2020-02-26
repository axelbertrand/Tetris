#include "SettingState.h"

SettingState::SettingState(StateStack& stack, Context context)
	: State(stack, context)
{
	mBackgroundSprite.setTexture(context.textures->get(TexturesID::BackGround));

	// Build key binding buttons and labels
	addButtonLabel(toUnderlyingType(PlayerAction::Type::MoveLeft), 0, 0, "Move Left", context);
	addButtonLabel(toUnderlyingType(PlayerAction::Type::MoveRight), 0, 1, "Move Right", context);
	addButtonLabel(toUnderlyingType(PlayerAction::Type::SoftDrop), 0, 2, "Soft Drop", context);
	addButtonLabel(toUnderlyingType(PlayerAction::Type::HardDrop), 0, 3, "Hard Drop", context);
	addButtonLabel(toUnderlyingType(PlayerAction::Type::Rotate), 0, 4, "Rotate", context);

	updateLabels();

	auto backButton = std::make_shared<gui::Button>(context);
	backButton->setPosition(80.f, 520.f);
	backButton->setText("Back");
	backButton->setCallback(std::bind(&SettingState::requestStackPop, this));

	mContainer.pack(backButton);
}

void SettingState::draw()
{
	sf::RenderWindow& window = *getContext().window;

	window.draw(mBackgroundSprite);
	window.draw(mContainer);
}

bool SettingState::update(sf::Time dt)
{
	return true;
}

bool SettingState::handleEvent(const sf::Event & event)
{
	bool isKeyBinding = false;

	// Iterate through all key binding buttons to see if they are being pressed, waiting for the user to enter a key
	for (std::size_t i = 0; i < toUnderlyingType(PlayerAction::Type::Count); ++i)
	{
		if (mBindingButtons[i]->isActive())
		{
			isKeyBinding = true;
			if (event.type == sf::Event::KeyReleased)
			{
				getContext().keyBinding->assignKey(static_cast<PlayerAction::Type>(i), event.key.code);
				mBindingButtons[i]->deactivate();
			}
			break;
		}
	}

	// If pressed button changed key bindings, update labels; otherwise consider other buttons in container
	if (isKeyBinding)
	{
		updateLabels();
	}
	else
	{
		mContainer.handleEvent(event);
	}

	return false;
}

void SettingState::updateLabels()
{
	for (std::size_t i = 0; i < toUnderlyingType(PlayerAction::Type::Count); ++i)
	{
		auto action = static_cast<PlayerAction::Type>(i);

		// Get keys of both players
		sf::Keyboard::Key key = getContext().keyBinding->getAssignedKey(action);

		// Assign both key strings to labels
		mBindingLabels[i]->setText(toString(key));
	}
}

void SettingState::addButtonLabel(std::size_t index, std::size_t x, std::size_t y, const std::string& text, Context context)
{
	mBindingButtons[index] = std::make_shared<gui::Button>(context);
	mBindingButtons[index]->setPosition(400.f * x + 80.f, 50.f * y + 250.f);
	mBindingButtons[index]->setText(text);
	mBindingButtons[index]->setToggle(true);

	mBindingLabels[index] = std::make_shared<gui::Label>("", *context.fonts);
	mBindingLabels[index]->setPosition(400.f * x + 300.f, 50.f * y + 265.f);

	mContainer.pack(mBindingButtons[index]);
	mContainer.pack(mBindingLabels[index]);
}
