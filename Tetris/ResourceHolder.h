#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

#include "ResourceIdentifiers.h"

namespace sf
{
	class Texture;
	class Font;
}

template <typename Resource, typename Identifier>
class ResourceHolder
{
	public:
		void load(Identifier id, const std::string& filename);

		template <typename Parameter>
		void load(Identifier id, const std::string& filename, const Parameter& secondParam);

		Resource& get(Identifier id);
		const Resource& get(Identifier id) const;


	private:
		void insertResource(Identifier id, std::unique_ptr<Resource> resource);

		std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};

using TextureHolder = ResourceHolder<sf::Texture, TexturesID>;
using FontHolder = ResourceHolder<sf::Font, FontsID>;

#include "ResourceHolder.inl"