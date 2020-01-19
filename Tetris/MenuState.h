#pragma once

#include "State.h"

class MenuState : public State
{
public:
	MenuState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;
};

