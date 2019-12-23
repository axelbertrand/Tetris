#pragma once

#include "GameLib.h"
#include "StateIdentifiers.h"
#include "ResourceHolder.h"
#include <memory>

class StateStack;

class State
{
public:
	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
	};

	State(StateStack& stack, Context context);
	virtual ~State() = default;

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

protected:
	void requestStackPush(StatesID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

private:
	StateStack* mStack;
	Context mContext;
};

