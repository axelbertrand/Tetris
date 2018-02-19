#pragma once

#include "State.h"

class SettingState : public State
{
	public:
		SettingState(StateStack& stack, Context context);

		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);
};

