#include "State.h"
#include "StateStack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, KeyBinding& keyBinding)
	: window(&window)
	, textures(&textures)
	, fonts(&fonts)
	, keyBinding(&keyBinding)
{
}

State::State(StateStack& stack, Context context)
	: mStack(&stack)
	, mContext(context)
{
}

void State::requestStackPush(StatesID stateID)
{
	mStack->pushState(stateID);
}

void State::requestStackPop()
{
	mStack->popState();
}

void State::requestStateClear()
{
	mStack->clearStates();
}

void State::save()
{
}

State::Context State::getContext() const
{
	return mContext;
}