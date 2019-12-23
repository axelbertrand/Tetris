#pragma once

#include "State.h"

class LoadingGameState : public State
{
public:
	LoadingGameState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);
};

