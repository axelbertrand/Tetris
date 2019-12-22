#pragma once

#include "GameLib.h"

#include "Command.h"
#include <vector>
#include <memory>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		void attachChild(std::unique_ptr<SceneNode> child);
		std::unique_ptr<SceneNode> detachChild(const SceneNode& node);

		void update(sf::Time dt);

		sf::Vector2f getWorldPosition() const;
		sf::Transform getWorldTransform() const;

		void onCommand(const Command& command, sf::Time dt);
		virtual Category getCategory() const;

	private:
		virtual void updateCurrent(sf::Time dt);
		void updateChildren(sf::Time dt);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		std::vector<std::unique_ptr<SceneNode>> mChildren;
		SceneNode* mParent{ nullptr };
};