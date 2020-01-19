#pragma once

#include "State.h"

class LoadingGameState : public State
{
public:
	LoadingGameState(StateStack& stack, Context context);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;
};

