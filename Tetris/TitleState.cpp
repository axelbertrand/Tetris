#include "TitleState.h"

TitleState::TitleState(StateStack& stack, Context context) :
State(stack, context)
{
}

void TitleState::draw()
{
}

bool TitleState::update(sf::Time dt)
{
	return false;
}

bool TitleState::handleEvent(const sf::Event & event)
{
	return false;
}
