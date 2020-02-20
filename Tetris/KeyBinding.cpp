#include "KeyBinding.h"

#include <string>
#include <algorithm>


KeyBinding::KeyBinding()
{
	// Set initial key bindings
	mKeyMap[sf::Keyboard::Left] = Action::MoveLeft;
	mKeyMap[sf::Keyboard::Right] = Action::MoveRight;
	mKeyMap[sf::Keyboard::Down] = Action::SoftDrop;
	mKeyMap[sf::Keyboard::Up] = Action::HardDrop;
	mKeyMap[sf::Keyboard::Space] = Action::Rotate;
}

void KeyBinding::assignKey(Action action, sf::Keyboard::Key key)
{
	// Remove all keys that already map to action
	for (auto itr = mKeyMap.begin(); itr != mKeyMap.end(); )
	{
		if (itr->second == action)
			mKeyMap.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyMap[key] = action;
}

sf::Keyboard::Key KeyBinding::getAssignedKey(Action action) const
{
	for(const auto& pair : mKeyMap)
	{
		if (pair.second == action)
		{
			return pair.first;
		}
	}

	return sf::Keyboard::Unknown;
}

bool KeyBinding::checkAction(sf::Keyboard::Key key, Action& out) const
{
	auto found = mKeyMap.find(key);
	if (found == mKeyMap.end())
	{
		return false;
	}
	else
	{
		out = found->second;
		return true;
	}
}

std::vector<KeyBinding::Action> KeyBinding::getRealtimeActions() const
{
	// Return all realtime actions that are currently active.
	std::vector<Action> actions;

	for(const auto& pair : mKeyMap)
	{
		// If key is pressed and an action is a realtime action, store it
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
		{
			actions.push_back(pair.second);
		}
	}

	return actions;
}

bool KeyBinding::isRealtimeAction(PlayerAction::Type action)
{
	switch (action)
	{
	default:
		return false;
	}
}