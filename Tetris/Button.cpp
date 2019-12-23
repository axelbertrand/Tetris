#include "Button.h"

namespace gui
{
	Button::Button(const FontHolder& fonts, const TextureHolder& textures)
		: mNormalTexture(textures.get(TexturesID::ButtonNormal))
		, mSelectedTexture(textures.get(TexturesID::ButtonSelected))
		, mPressedTexture(textures.get(TexturesID::ButtonPressed))
		, mText("", fonts.get(FontsID::Main), 16)
	{
		mSprite.setTexture(mNormalTexture);

		sf::FloatRect bounds = mSprite.getLocalBounds();
		mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	}

	void Button::setCallback(Callback callback)
	{
		mCallback = std::move(callback);
	}

	void Button::setText(const std::string& text)
	{
		mText.setString(text);
		sf::FloatRect bounds = mText.getLocalBounds();
		mText.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	}

	void Button::setToggle(bool flag)
	{
		mIsToggle = flag;
	}

	bool Button::isSelectable() const
	{
		return true;
	}

	void Button::select()
	{
		Component::select();

		mSprite.setTexture(mSelectedTexture);
	}

	void Button::deselect()
	{
		Component::deselect();

		mSprite.setTexture(mNormalTexture);
	}

	void Button::activate()
	{
		Component::activate();

		if (mIsToggle)
			mSprite.setTexture(mPressedTexture);

		if (mCallback)
			mCallback();

		if (!mIsToggle)
			deactivate();
	}

	void Button::deactivate()
	{
		Component::deactivate();

		if (mIsToggle)
		{
			// Reset texture to right one depending on if we are selected or not.
			if (isSelected())
				mSprite.setTexture(mSelectedTexture);
			else
				mSprite.setTexture(mNormalTexture);
		}
	}

	void Button::handleEvent(const sf::Event&)
	{
	}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mSprite, states);
		target.draw(mText, states);
	}

}