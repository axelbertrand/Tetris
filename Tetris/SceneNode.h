#pragma once

#include "Defs.h"

#include "Command.h"
#include <vector>
#include <memory>

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable
{
	public:
		typedef std::unique_ptr<SceneNode> Ptr;

		SceneNode();

		void attachChild(Ptr child);
		Ptr detachChild(const SceneNode& node);

		void update(sf::Time dt);

		sf::Vector2f getWorldPosition() const;
		sf::Transform getWorldTransform() const;

		void onCommand(const Command& command, sf::Time dt);
		virtual Category getCategory() const;

		virtual sf::FloatRect getBoundingRect() const;

	private:
		virtual void updateCurrent(sf::Time dt);
		void updateChildren(sf::Time dt);

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
		void drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;


	private:
		std::vector<Ptr> mChildren;
		SceneNode* mParent;
};