#pragma once

#include "State.h"
#include "Container.h"

class TitleState : public State
{
public :
	TitleState(StateStack& stack, Context context);
		
	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

private :
	sf::Text mTetrisTitle;
	gui::Container mContainer;
};

