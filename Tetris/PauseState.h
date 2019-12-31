#pragma once

#include "State.h"
#include "Container.h"

class PauseState : public State
{
public:
	PauseState(StateStack& stack, Context context, bool letUpdateThrough = false);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Text mPauseText;
	gui::Container mContainer;
	bool mLetUpdateThrough;
};