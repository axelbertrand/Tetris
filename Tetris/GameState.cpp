#include "GameState.h"

GameState::GameState(StateStack& stack, Context context)
	: State(stack, context)
	, mWorld(*context.window, *context.textures, *context.fonts)
{ 
}

void GameState::draw()
{
	mWorld.draw();
}

bool GameState::update(sf::Time dt)
{
	mWorld.update(dt);

	if (mWorld.isGameFinished())
	{
		requestStateClear();
		requestStackPush(StatesID::Title);
	}

	std::queue<Command>& commands = mWorld.getCommandQueue();
	mPlayer.handleRealtimeInput(commands);

	return true;
}

bool GameState::handleEvent(const sf::Event & event)
{
	std::queue<Command>& commands = mWorld.getCommandQueue();
	mPlayer.handleEvent(event, commands);

	// Press Escape key to pause the game
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
	{
		requestStackPush(StatesID::Pause);
	}

	return true;
}

void GameState::save()
{
	mWorld.save(SAVE_FILE_PATH);
}
