#pragma once

#include "Component.h"

namespace gui
{
	class Container : public Component
	{
	public:
		void pack(std::shared_ptr<Component> component);

		virtual bool isSelectable() const;
		virtual void handleEvent(const sf::Event& event);

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

		bool hasSelection() const;
		void select(std::size_t index);
		void selectNext();
		void selectPrevious();

		std::vector<std::shared_ptr<Component>> mChildren;
		int mSelectedChild{ -1 };
	};
}