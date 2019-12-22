#include "LoadingGameState.h"

LoadingGameState::LoadingGameState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void LoadingGameState::draw()
{
}

bool LoadingGameState::update(sf::Time dt)
{
	return false;
}

bool LoadingGameState::handleEvent(const sf::Event & event)
{
	return false;
}
