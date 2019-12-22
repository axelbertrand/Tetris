#pragma once

#include "Defs.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"

class TextNode : public SceneNode
{
public:
	explicit TextNode(const std::string& text, const FontHolder& fonts);

	void setString(const std::string& text);

private:
	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text mText;
};