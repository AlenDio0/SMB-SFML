#include "TileMap.hpp"

namespace Core
{
	TileMap::TileMap(sf::Vector2u mapSize, float tileSize, const SpriteSheet& tileSheet) noexcept
		: m_TilePool(mapSize.x* mapSize.y, 0), m_MapSize(mapSize), m_TileSize(tileSize), m_TileSheet(tileSheet)
	{
	}

	const sf::Vector2u& TileMap::GetMapSize() const noexcept
	{
		return m_MapSize;
	}

	const float& TileMap::GetTileSize() const noexcept
	{
		return m_TileSize;
	}

	const SpriteSheet& TileMap::GetTileSheet() const noexcept
	{
		return m_TileSheet;
	}

	void TileMap::ResizeMap(sf::Vector2u newSize) noexcept
	{
		if (m_MapSize == newSize)
			return;

		if (newSize.x == 0 && newSize.y == 0)
		{
			m_TilePool.clear();
			m_MapSize = newSize;
			return;
		}

		const auto [deltaX, deltaY] = (sf::Vector2i)(newSize - m_MapSize);
		if (deltaY < 0)
			ShrinkSizeY(newSize.y);
		if (deltaX > 0)
			ExpandSizeX(newSize.x);
		if (deltaX < 0)
			ShrinkSizeX(newSize.x);
		if (deltaY > 0)
			ExpandSizeY(newSize.y);
	}

	void TileMap::setTileSize(float newSize) noexcept
	{
		m_TileSize = newSize;
	}

	void TileMap::SetTile(sf::Vector2u position, uint32_t id) noexcept
	{
		if (position.x >= m_MapSize.x || position.y >= m_MapSize.y)
			return;

		m_TilePool.at(GetIndex(position)) = id;
	}

	uint32_t TileMap::GetTile(sf::Vector2u position) const noexcept
	{
		if (position.x >= m_MapSize.x || position.y >= m_MapSize.y)
			return 0;

		return m_TilePool.at(GetIndex(position));
	}

	void TileMap::Render(sf::RenderTarget& target) const noexcept
	{
		sf::RectangleShape tileShape(sf::Vector2f(m_TileSize, m_TileSize));
		tileShape.setTexture(m_TileSheet._TexturePtr);

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

	size_t Core::TileMap::GetIndex(sf::Vector2u position) const noexcept
	{
		return (size_t)(position.y * m_MapSize.x) + position.x;
	}

	void TileMap::ShrinkSizeX(uint32_t newSizeX) noexcept
	{
		std::vector<uint32_t> newTiles;
		newTiles.reserve((size_t)(newSizeX * m_MapSize.y));

		for (uint32_t y = 0; y < m_MapSize.y; y++)
		{
			for (uint32_t x = 0; x < newSizeX; x++)
			{
				uint32_t id = m_TilePool.at(GetIndex(sf::Vector2u(x, y)));
				newTiles.emplace_back(id);
			}
		}

		m_TilePool = newTiles;
		m_MapSize.x = newSizeX;
	}

	void TileMap::ExpandSizeX(uint32_t newSizeX) noexcept
	{
		std::vector<uint32_t> newTiles;
		newTiles.reserve((size_t)(newSizeX * m_MapSize.y));

		for (uint32_t y = 0; y < m_MapSize.y; y++)
		{
			for (uint32_t x = 0; x < newSizeX; x++)
			{
				uint32_t id = 0u;
				if (x < m_MapSize.x)
					id = m_TilePool.at(GetIndex(sf::Vector2u(x, y)));

				newTiles.emplace_back(id);
			}
		}

		m_TilePool = newTiles;
		m_MapSize.x = newSizeX;
	}

	void TileMap::ShrinkSizeY(uint32_t newSizeY) noexcept
	{
		m_TilePool.erase(m_TilePool.begin() + GetIndex(sf::Vector2u(0, newSizeY + 1)), m_TilePool.end());

		m_MapSize.y = newSizeY;
	}

	void TileMap::ExpandSizeY(uint32_t newSizeY) noexcept
	{
		m_TilePool.reserve((size_t)(m_MapSize.x * newSizeY));
		for (uint32_t i = 0; i < (newSizeY - m_MapSize.y) * m_MapSize.x; i++)
			m_TilePool.emplace_back(0u);

		m_MapSize.y = newSizeY;
	}
}
