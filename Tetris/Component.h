#pragma once

#include "GameLib.h"
#include <memory>

namespace gui
{
	class Component : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual bool isSelectable() const = 0;
		bool isSelected() const;
		virtual void select();
		virtual void deselect();

		virtual bool isActive() const;
		virtual void activate();
		virtual void deactivate();

		virtual void handleEvent(const sf::Event& event) = 0;

	private:
		bool mIsSelected{ false };
		bool mIsActive{ false };
	};
}