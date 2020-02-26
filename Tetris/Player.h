#pragma once

#include "Command.h"
#include "KeyBinding.h"
#include <SFML/Window/Event.hpp>
#include <queue>
#include <map>

class Player
{
public :
	using Action = PlayerAction::Type;

	explicit Player(KeyBinding keyBinding);

	void handleEvent(const sf::Event& event, std::queue<Command>& commands);
	void handleRealtimeInput(std::queue<Command>& commands);

private :
	void initializeActions();

	KeyBinding mKeyBinding;
	std::map<Action, Command> mActionBinding;
};

