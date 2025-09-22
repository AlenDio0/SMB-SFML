#pragma once
#include <SFML/Graphics.hpp>
#include <optional>

namespace Core
{
	class SpriteSheet
	{
	public:
		SpriteSheet(const sf::Texture& texture, sf::Vector2u size, sf::Vector2u spriteSize) noexcept;
		~SpriteSheet() noexcept = default;

		uint32_t GetSizeID() const noexcept;

		std::optional<sf::IntRect> GetRect(uint32_t id) const noexcept;
		std::optional<sf::IntRect> GetRect(sf::Vector2i position) const noexcept;
	public:
		const sf::Texture* _TexturePtr = nullptr;

		const sf::Vector2u _Size;
		const sf::Vector2u _SpriteSize;
	};
}
