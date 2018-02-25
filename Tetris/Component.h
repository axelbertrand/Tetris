#pragma once

#include "Defs.h"
#include <memory>

namespace gui
{

	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
		public:
			typedef std::shared_ptr<Component> Ptr;

			Component();
			virtual ~Component();

			virtual bool isSelectable() const = 0;
			bool isSelected() const;
			virtual void select();
			virtual void deselect();

			virtual bool isActive() const;
			virtual void activate();
			virtual void deactivate();

			virtual void handleEvent(const sf::Event& event) = 0;


		private:
			bool mIsSelected;
			bool mIsActive;
	};

}