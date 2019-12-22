#include "StateStack.h"

StateStack::StateStack(State::Context context)
	: mContext(context)
{
}

void StateStack::update(sf::Time dt)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->update(dt))
		{
			break;
		}
	}

	applyPendingChanges();
}

void StateStack::draw()
{
	for (std::unique_ptr<State>& state : mStack)
	{
		state->draw();
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
	for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
	{
		if (!(*itr)->handleEvent(event))
		{
			break;
		}
	}

	applyPendingChanges();
}

void StateStack::pushState(StatesID stateID)
{
	mPendingList.push_back(PendingChange(Action::Push, stateID));
}

void StateStack::popState()
{
	mPendingList.push_back(PendingChange(Action::Pop));
}

void StateStack::clearStates()
{
	mPendingList.push_back(PendingChange(Action::Clear));
}

bool StateStack::isEmpty() const
{
	return mStack.empty();
}

std::unique_ptr<State> StateStack::createState(StatesID stateID)
{
	auto found = mFactories.find(stateID);

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for(PendingChange change : mPendingList)
	{
		switch (change.action)
		{
		case Action::Push :
			mStack.push_back(createState(change.stateID));
			break;

		case Action::Pop :
			mStack.pop_back();
			break;

		case Action::Clear :
			mStack.clear();
			break;
		}
	}

	mPendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, StatesID stateID)
	: action(action)
	, stateID(stateID)
{
}