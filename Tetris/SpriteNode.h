#pragma once

#include "SceneNode.h"

class SpriteNode : public SceneNode
{
public:
	explicit SpriteNode(const sf::Texture& texture);
	SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect);

private:
	void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite mSprite;
};