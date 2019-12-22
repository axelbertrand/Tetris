#include "Player.h"

#include "Grid.h"

struct TetrominoMover
{
	TetrominoMover(int vx, int vy)
		: velocity(vx, vy)
	{
	}

	void operator() (Grid& grid, sf::Time dt) const
	{
		grid.moveCurrentTetromino(velocity);
	}

	sf::Vector2i velocity;
};

struct TetrominoRotator
{
	void operator() (Grid& grid, sf::Time dt) const
	{
		grid.rotateCurrentTetromino();
	}
};

struct TetrominoHardDropper
{
	void operator() (Grid& grid, sf::Time dt) const
	{
		grid.hardDropCurrentTetromino();
	}
};

Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = Action::MoveRight;
	mKeyBinding[sf::Keyboard::Down] = Action::SoftDrop;
	mKeyBinding[sf::Keyboard::Up] = Action::HardDrop;
	mKeyBinding[sf::Keyboard::Space] = Action::Rotate;

	initializeActions();

	for(auto& pair : mActionBinding)
		pair.second.category = Category::Grid;
}

Player::~Player()
{
}

void Player::handleEvent(const sf::Event& event, std::queue<Command>& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
			commands.push(mActionBinding[found->second]);
	}
}

void Player::handleRealtimeInput(std::queue<Command>& commands)
{
	for(auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for(auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions()
{
	mActionBinding[Action::MoveLeft].action = derivedAction<Grid>(TetrominoMover(-1, 0));
	mActionBinding[Action::MoveRight].action = derivedAction<Grid>(TetrominoMover(1, 0));
	mActionBinding[Action::SoftDrop].action = derivedAction<Grid>(TetrominoMover(0, 1));
	mActionBinding[Action::HardDrop].action = derivedAction<Grid>(TetrominoHardDropper());
	mActionBinding[Action::Rotate].action = derivedAction<Grid>(TetrominoRotator());
}

bool Player::isRealtimeAction(Player::Action action)
{
	switch (action)
	{
		default :
			return false;
	}
}
