#pragma once

#include "GameLib.h"
#include "State.h"
#include "StateIdentifiers.h"
#include <vector>
#include <utility>
#include <functional>
#include <map>

class StateStack : private sf::NonCopyable
{
public :
	enum class Action
	{
		Push,
		Pop,
		Clear,
	};

	explicit StateStack(State::Context context);

	template <typename T, typename... Args>
	void registerState(StatesID stateID, Args... args);

	void update(sf::Time dt);
	void draw();
	void handleEvent(const sf::Event& event);

	void pushState(StatesID stateID);
	void popState();
	void clearStates();

	bool isEmpty() const;

private :
	std::unique_ptr<State> createState(StatesID stateID);
	void applyPendingChanges();

	struct PendingChange
	{
		explicit PendingChange(Action action, StatesID stateID = StatesID::None);

		Action action;
		StatesID stateID;
	};

	std::vector<std::unique_ptr<State>> mStack;
	std::vector<PendingChange> mPendingList;

	State::Context mContext;
	std::map<StatesID, std::function<std::unique_ptr<State>()>> mFactories;
};


template <typename T, typename... Args>
void StateStack::registerState(StatesID stateID, Args... args)
{
	mFactories[stateID] = [this]()
	{
		return std::make_unique<T>(*this, mContext, args...);
	};
}

