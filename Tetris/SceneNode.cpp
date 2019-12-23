#include "SceneNode.h"

#include <algorithm>
#include <cassert>

void SceneNode::attachChild(std::unique_ptr<SceneNode> child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}

std::unique_ptr<SceneNode> SceneNode::detachChild(const SceneNode& node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](std::unique_ptr<SceneNode>& p) { return p.get() == &node; });
	assert(found != mChildren.end());

	std::unique_ptr<SceneNode> result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);

	return result;
}

void SceneNode::update(sf::Time dt)
{
	updateCurrent(dt);
	updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time)
{
}

void SceneNode::updateChildren(sf::Time dt)
{
	for (std::unique_ptr<SceneNode>& child : mChildren)
	{
		child->update(dt);
	}
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const
{
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const std::unique_ptr<SceneNode>& child : mChildren)
	{
		child->draw(target, states);
	}
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
	{
		transform = node->getTransform() * transform;
	}

	return transform;
}

void SceneNode::onCommand(const Command & command, sf::Time dt)
{
	if (command.category == getCategory())
	{
		command.action(*this, dt);
	}

	for (std::unique_ptr<SceneNode>& child : mChildren)
	{
		child->onCommand(command, dt);
	}
}

Category SceneNode::getCategory() const
{
	return Category::Scene;
}
