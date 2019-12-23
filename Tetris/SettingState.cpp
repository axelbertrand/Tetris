#include "SettingState.h"

SettingState::SettingState(StateStack& stack, Context context)
	: State(stack, context)
{
}

void SettingState::draw()
{
}

bool SettingState::update(sf::Time dt)
{
	return false;
}

bool SettingState::handleEvent(const sf::Event & event)
{
	return false;
}
