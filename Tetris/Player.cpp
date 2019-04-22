#include "Player.h"

#include "Tetromino.h"

struct TetrominoMover
{
	TetrominoMover(float vx, float vy) :
	velocity(vx, vy)
	{
	}

	void operator() (Tetromino& tetromino, sf::Time dt) const
	{
		tetromino.move(velocity);
	}

	sf::Vector2f velocity;
};

struct TetrominoRotator
{
	void operator() (Tetromino& tetromino, sf::Time dt) const
	{
		tetromino.rotate(90.f);
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
		pair.second.category = Category::CurrentTetromino;
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
	const float playerSpeed = 20.f;

	mActionBinding[Action::MoveLeft].action = derivedAction<Tetromino>(TetrominoMover(-playerSpeed, 0.f));
	mActionBinding[Action::MoveRight].action = derivedAction<Tetromino>(TetrominoMover(+playerSpeed, 0.f));
	mActionBinding[Action::SoftDrop].action = derivedAction<Tetromino>(TetrominoMover(0.f, +playerSpeed));
	mActionBinding[Action::HardDrop].action = derivedAction<Tetromino>(TetrominoMover(0.f, -playerSpeed));
	mActionBinding[Action::Rotate].action = derivedAction<Tetromino>(TetrominoRotator());
}

bool Player::isRealtimeAction(Player::Action action)
{
	switch (action)
	{
		case Action::MoveLeft :
		case Action::MoveRight :
		case Action::SoftDrop:
		case Action::HardDrop :
			return true;

		default :
			return false;
	}
}
