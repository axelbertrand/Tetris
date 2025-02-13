#pragma once

#include "GameLib.h"
#include "StateIdentifiers.h"
#include "ResourceHolder.h"
#include "KeyBinding.h"
#include <memory>

class StateStack;

class State
{
public:
	struct Context
	{
		Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, KeyBinding& keyBinding);

		sf::RenderWindow* window;
		TextureHolder* textures;
		FontHolder* fonts;
		KeyBinding* keyBinding;
	};

	State(StateStack& stack, Context context);
	virtual ~State() = default;

	virtual void draw() = 0;
	virtual bool update(sf::Time dt) = 0;
	virtual bool handleEvent(const sf::Event& event) = 0;

	virtual void save();

protected:
	void requestStackPush(StatesID stateID);
	void requestStackPop();
	void requestStateClear();

	Context getContext() const;

	StateStack* mStack;
private:
	Context mContext;
};

