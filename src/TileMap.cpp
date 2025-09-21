#include "TileMap.hpp"

namespace SMB
{
	TileMap::TileMap(SpriteSheet tileSheet, sf::Vector2u mapSize, float tileSize) noexcept
		: m_Tiles(mapSize.x* mapSize.y, 0), m_TileSheet(tileSheet), m_MapSize(mapSize), m_TileSize(tileSize)
	{
	}

	sf::Vector2u TileMap::GetMapSize() const noexcept
	{
		return m_MapSize;
	}

	float TileMap::GetTileSize() const noexcept
	{
		return m_TileSize;
	}

	void TileMap::SetTile(sf::Vector2u position, uint32_t id) noexcept
	{
		if (position.x >= m_MapSize.x || position.y >= m_MapSize.y)
			return;

		m_Tiles.at(GetIndex(position)) = id;
	}

	uint32_t TileMap::GetTile(sf::Vector2u position) const noexcept
	{
		if (position.x >= m_MapSize.x || position.y >= m_MapSize.y)
			return 0;

		return m_Tiles.at(GetIndex(position));
	}

	void TileMap::Render(sf::RenderTarget& target) const noexcept
	{
		sf::RectangleShape tileShape(sf::Vector2f(m_TileSize, m_TileSize));
		tileShape.setTexture(m_TileSheet._Texture);

		for (uint32_t y = 0; y < m_MapSize.y; y++)
		{
			for (uint32_t x = 0; x < m_MapSize.x; x++)
			{
				auto textureRect = m_TileSheet.GetRect(GetTile(sf::Vector2u(x, y)));
				if (!textureRect.has_value())
					continue;

				tileShape.setPosition(sf::Vector2f(x * m_TileSize, y * m_TileSize));
				tileShape.setTextureRect(textureRect.value());

				target.draw(tileShape);
			}
		}
	}

	uint32_t TileMap::GetIndex(sf::Vector2u position) const noexcept
	{
		return (position.y * m_MapSize.x) + position.x;
	}
}
