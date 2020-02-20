#include "GameState.h"

#include <fstream>

GameState::GameState(StateStack& stack, Context context, bool loadWorld)
	: State(stack, context)
	, mWorld(*context.window, *context.textures, *context.fonts)
	, mPlayer(*context.keyBinding)
{ 
	if (loadWorld)
	{
		std::ifstream inputFileStream(SAVE_FILE_PATH, std::ios::binary);
		mWorld.load(std::move(inputFileStream));
	}
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
	std::ofstream outputFileStream(SAVE_FILE_PATH, std::ios::binary | std::ios::trunc);
	mWorld.save(std::move(outputFileStream));
}
