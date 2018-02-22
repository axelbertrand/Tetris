#pragma once

#include "State.h"

class TitleState : public State
{
	public :
		TitleState(StateStack& stack, Context context);
		
		virtual void draw();
		virtual bool update(sf::Time dt);
		virtual bool handleEvent(const sf::Event& event);

	private :
		sf::Text mTetrisTitle;
		sf::Text mNewGameButton;
		sf::Text mLoadGameButton;
		sf::Text mSettingsButton;
		sf::Text mQuitButton;
};

