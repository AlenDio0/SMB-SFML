#pragma once
#include <unordered_map>
#include <string_view>
#include <SFML/System/Vector2.hpp>
#include <sstream>

namespace Core
{
	struct Sprite
	{
		sf::Vector2u _Position;
		// TODO: Add flags & etc...
	};

	class SpriteBank
	{
	public:
		SpriteBank() noexcept = default;
		~SpriteBank() noexcept = default;

		void LoadSprite(std::stringstream&& data) noexcept;
		void AddSprite(std::string_view key, const Sprite& sprite) noexcept;

		const Sprite& GetSprite(std::string_view key) const;
	private:
		std::unordered_map<std::string_view, Sprite> m_Sprites;
	};
}
