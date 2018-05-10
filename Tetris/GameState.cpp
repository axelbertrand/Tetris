#include "GameState.h"

GameState::GameState(StateStack& stack, Context context) :
State(stack, context),
mWorld(*context.window, *context.textures, *context.fonts),
mPlayer()
{
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	return true;
}

bool GameState::handleEvent(const sf::Event & event)
{
	return false;
}
