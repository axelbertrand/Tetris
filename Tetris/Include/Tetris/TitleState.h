#pragma once

#include "State.h"
#include "Container.h"

class TitleState : public State
{
	public :
		TitleState(StateStack& stack, Context context);
		
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);

	private :
		sf::Text mTetrisTitle;
		gui::Container mContainer;
};

