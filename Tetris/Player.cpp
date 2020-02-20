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

Player::Player(KeyBinding keyBinding)
	: mKeyBinding(keyBinding)
{
	initializeActions();

	for(auto& pair : mActionBinding)
		pair.second.category = Category::Grid;
}

void Player::handleEvent(const sf::Event& event, std::queue<Command>& commands)
{
	if (event.type == sf::Event::KeyPressed)
	{
		Action action;
		if (mKeyBinding.checkAction(event.key.code, action) && !KeyBinding::isRealtimeAction(action))
		{
			commands.push(mActionBinding[action]);
		}
	}
}

void Player::handleRealtimeInput(std::queue<Command>& commands)
{
	std::vector<Action> activeActions = mKeyBinding.getRealtimeActions();
	for(const Action& action : activeActions)
	{
		commands.push(mActionBinding[action]);
	}
}

void Player::initializeActions()
{
	mActionBinding[Action::MoveLeft].action	= derivedAction<Grid>(TetrominoMover(-1, 0));
	mActionBinding[Action::MoveRight].action = derivedAction<Grid>(TetrominoMover(1, 0));
	mActionBinding[Action::SoftDrop].action = derivedAction<Grid>(TetrominoMover(0, 1));
	mActionBinding[Action::HardDrop].action = derivedAction<Grid>(TetrominoHardDropper());
	mActionBinding[Action::Rotate].action = derivedAction<Grid>(TetrominoRotator());
}
