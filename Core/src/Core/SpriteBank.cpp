#include "SpriteBank.hpp"
#include <string>

namespace Core
{
	void SpriteBank::LoadSprite(std::stringstream&& data) noexcept
	{
		std::string key;
		Sprite sprite;

		while (!data.eof())
		{
			std::string buffer;
			data >> buffer;

			if (buffer == "SPRITE")
				data >> key;
			else if (buffer == "POSITION")
				data >> sprite._Position.x >> sprite._Position.y;
		}

		AddSprite(key, sprite);
	}

	void SpriteBank::AddSprite(std::string_view key, const Sprite& sprite) noexcept
	{
		m_Sprites.emplace(key, sprite);
	}

	const Sprite& SpriteBank::GetSprite(std::string_view key) const
	{
		if (!m_Sprites.contains(key))
			throw std::runtime_error("Sprite not found: " + std::string(key));

		return m_Sprites.at(key);
	}
}
