#include "SpriteSheet.hpp"
#include "AssetManager.hpp"
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>

namespace Core
{
	SpriteSheet::SpriteSheet(const std::filesystem::path& path, const AssetManager& assets)
		: SpriteSheet(LoadFromFile(path, assets))
	{
	}

	SpriteSheet::SpriteSheet(const sf::Texture& texture, sf::Vector2u size, sf::Vector2u spriteSize, const SpriteBank& sprites) noexcept
		: _TexturePtr(&texture), _Size(size), _SpriteSize(spriteSize), m_Sprites(sprites)
	{
	}

	uint32_t SpriteSheet::GetIDSize() const noexcept
	{
		return _Size.x * _Size.y;
	}

	const Sprite& SpriteSheet::GetSprite(std::string_view key) const
	{
		return m_Sprites.GetSprite(key);
	}

	sf::Vector2u SpriteSheet::GetPosition(uint32_t id) const noexcept
	{
		return sf::Vector2u(id % _Size.x, floor(id / _Size.x));
	}

	uint32_t SpriteSheet::GetID(sf::Vector2u position) const noexcept
	{
		return position.y * _Size.x + position.x;
	}

	std::optional<sf::IntRect> SpriteSheet::GetRect(const Sprite& sprite) const noexcept
	{
		return GetRect(sprite._Position);
	}

	std::optional<sf::IntRect> SpriteSheet::GetRect(uint32_t id) const noexcept
	{
		return GetRect(GetPosition(id));
	}

	std::optional<sf::IntRect> SpriteSheet::GetRect(sf::Vector2u position) const noexcept
	{
		if (position.x >= _Size.x || position.y >= _Size.y)
			return std::nullopt;

		return sf::IntRect((sf::Vector2i)position.componentWiseMul((sf::Vector2u)_SpriteSize), (sf::Vector2i)_SpriteSize);
	}

	SpriteSheet SpriteSheet::LoadFromFile(const std::filesystem::path& path, const AssetManager& assets)
	{
		std::ifstream file(path);
		if (!file.is_open())
			throw std::runtime_error("Unable to open file: " + path.string());

		std::string textureBuffer;
		sf::Vector2u size;
		sf::Vector2u spriteSize;
		SpriteBank sprites;

		while (!file.eof())
		{
			std::string buffer;
			file >> buffer;

			if (buffer == "TEXTURE")
			{
				file >> textureBuffer;
				continue;
			}
			else if (buffer == "SIZE")
			{
				file >> size.x >> size.y;
				continue;
			}
			else if (buffer == "SPRITESIZE")
			{
				file >> spriteSize.x >> spriteSize.y;
				continue;
			}

			if (buffer == "SPRITE")
			{
				std::stringstream spriteData;
				spriteData << buffer << " ";
				while (buffer != "END")
				{
					file >> buffer;
					spriteData << buffer << " ";
				}
				sprites.LoadSprite(std::move(spriteData));
			}
		}

		return SpriteSheet(assets.GetTexture(textureBuffer), size, spriteSize, sprites);
	}
}
