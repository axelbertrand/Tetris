#pragma once

#include "Component.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include <functional>

namespace gui
{
	class Button : public Component
	{
	public:
		using Callback = std::function<void()>;

		Button(const FontHolder& fonts, const TextureHolder& textures);

		void setCallback(Callback callback);
		void setText(const std::string& text);
		void setToggle(bool flag);

		bool isSelectable() const override;
		void select() override;
		void deselect() override;

		void activate() override;
		void deactivate() override;

		void handleEvent(const sf::Event& event) override;

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		Callback mCallback;
		const sf::Texture& mNormalTexture;
		const sf::Texture& mSelectedTexture;
		const sf::Texture& mPressedTexture;
		sf::Sprite mSprite;
		sf::Text mText;
		bool mIsToggle{ false };
	};
}