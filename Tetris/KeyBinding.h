#pragma once

#include "GameLib.h"

#include <map>
#include <vector>


namespace PlayerAction
{
	enum class Type
	{
		MoveLeft,
		MoveRight,
		SoftDrop,
		HardDrop,
		Rotate,
		Count
	};
}

class KeyBinding
{
public:
	using Action = PlayerAction::Type;

	explicit KeyBinding();

	void assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getAssignedKey(Action action) const;

	bool checkAction(sf::Keyboard::Key key, Action& out) const;
	std::vector<Action> getRealtimeActions() const;

	static bool isRealtimeAction(PlayerAction::Type action);

private:
	std::map<sf::Keyboard::Key, Action> mKeyMap;
};