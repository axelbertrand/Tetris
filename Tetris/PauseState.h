#pragma once

#include "State.h"
#include "Container.h"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context, bool letUpdateThrough = false);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

private:
	sf::Text mPauseText;
	gui::Container mContainer;
	bool mLetUpdateThrough;
};