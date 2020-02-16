#pragma once

#include "State.h"
#include "World.h"
#include "Player.h"

class GameState : public State
{
public:
	GameState(StateStack& stack, Context context, bool loadWorld = false);

	void draw() override;
	bool update(sf::Time dt) override;
	bool handleEvent(const sf::Event& event) override;

	void save() override;

private :
	const std::string SAVE_FILE_PATH{ "tetris_save.dat" };

	World mWorld;
	Player mPlayer;
};

