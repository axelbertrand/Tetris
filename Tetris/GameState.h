#pragma once

#include "State.h"
#include "World.h"
#include "Player.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context);

	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

	virtual void save();

private :
	const std::string SAVE_FILE_PATH{ "tetris_save.dat" };

	World mWorld;
	Player mPlayer;
};

