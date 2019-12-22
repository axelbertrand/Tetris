#pragma once

#include "Command.h"
#include <SFML/Window/Event.hpp>
#include <queue>
#include <map>

class Player
{
	public :
		enum class Action
		{
			MoveLeft,
			MoveRight,
			SoftDrop,
			HardDrop,
			Rotate,
			Hold,
			ActionCount
		};

		Player();
		~Player();

		void handleEvent(const sf::Event& event, std::queue<Command>& commands);
		void handleRealtimeInput(std::queue<Command>& commands);

		void assignKey(Action action, sf::Keyboard::Key key);
		sf::Keyboard::Key getAssignedKey(Action action) const;

	private :
		void initializeActions();
		static bool isRealtimeAction(Action action);

		std::map<sf::Keyboard::Key, Action> mKeyBinding;
		std::map<Action, Command> mActionBinding;
};

