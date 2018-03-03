#include "GameState.h"

GameState::GameState(StateStack& stack, Context context) :
State(stack, context),
mWorld(*context.window, *context.textures, *context.fonts)
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	return false;
}

bool GameState::handleEvent(const sf::Event & event)
{
	return false;
}
