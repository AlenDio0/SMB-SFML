#include "SpriteSheet.hpp"
#include <cmath>

namespace Core
{
	SpriteSheet::SpriteSheet(const sf::Texture& texture, sf::Vector2u size, sf::Vector2u spriteSize) noexcept
		: _TexturePtr(&texture), _Size(size), _SpriteSize(spriteSize)
	{
	}

	uint32_t SpriteSheet::GetSizeID() const noexcept
	{
		return _Size.x * _Size.y;
	}

	std::optional<sf::IntRect> SpriteSheet::GetRect(uint32_t id) const noexcept
	{
		return GetRect(sf::Vector2i(id % _Size.x, floor(id / _Size.x)));
	}

	std::optional<sf::IntRect> SpriteSheet::GetRect(sf::Vector2i position) const noexcept
	{
		if (position.x >= _Size.x || position.y >= _Size.y)
			return std::nullopt;

		return sf::IntRect(position.componentWiseMul((sf::Vector2i)_SpriteSize), (sf::Vector2i)_SpriteSize);
	}
}
