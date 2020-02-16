#pragma once

#include "State.h"

class SettingState : public State
{
public:
	SettingState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;
};

