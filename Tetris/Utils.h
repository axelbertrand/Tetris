#pragma once

#include <type_traits>
#include <sstream>

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

namespace std
{
	template <>
	struct hash<sf::Vector2u>
	{
		std::size_t operator()(const sf::Vector2u& vector) const
		{
			// Compute individual hash values for x and y
			// and combine them using XOR and bit shifting
			return (std::hash<unsigned int>()(vector.x) ^ (hash<unsigned int>()(vector.y) << 1));
		}
	};
}

template <typename E>
constexpr auto toUnderlyingType(E e) noexcept
{
    return static_cast<std::underlying_type_t<E>>(e);
}

template <typename T>
std::string toString(const T& value)
{
	std::stringstream stream;
	stream << value;
	return stream.str();
}

std::string toString(const sf::Keyboard::Key& key);