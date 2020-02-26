#pragma once

#include "Component.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Text.hpp>


namespace gui
{
    class Label : public Component
    {
    public:
        Label(const std::string& text, const FontHolder& fonts);

        virtual bool isSelectable() const;
        void setText(const std::string& text);

        virtual void handleEvent(const sf::Event& event);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        sf::Text mText;
    };
}