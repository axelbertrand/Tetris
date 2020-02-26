#pragma once

#include <memory>
#include <array>

#include "State.h"
#include "KeyBinding.h"
#include "Container.h"
#include "Button.h"
#include "Label.h"
#include "Utils.h"

#include <SFML/Graphics/Sprite.hpp>

class SettingState : public State
{
public:
	SettingState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

private:
	void updateLabels();
	void addButtonLabel(std::size_t index, std::size_t x, std::size_t y, const std::string& text, Context context);

	sf::Sprite mBackgroundSprite;
	gui::Container mContainer;
	std::array<std::shared_ptr<gui::Button>, toUnderlyingType(PlayerAction::Type::Count)> mBindingButtons;
	std::array<std::shared_ptr<gui::Label>, toUnderlyingType(PlayerAction::Type::Count)> mBindingLabels;
};

