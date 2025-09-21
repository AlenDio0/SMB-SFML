#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "SpriteSheet.hpp"

namespace Core
{
	class TileMap
	{
	public:
		TileMap(sf::Vector2u mapSize, float tileSize, const SpriteSheet& tileSheet) noexcept;
		~TileMap() noexcept = default;

		const sf::Vector2u& GetMapSize() const noexcept;
		const float& GetTileSize() const noexcept;
		const SpriteSheet& GetTileSheet() const noexcept;

		void ResizeMap(sf::Vector2u newSize) noexcept;
		void setTileSize(float newSize) noexcept;

		void SetTile(sf::Vector2u position, uint32_t id) noexcept;
		uint32_t GetTile(sf::Vector2u position) const noexcept;

		void Render(sf::RenderTarget& target) const noexcept;
	private:
		size_t GetIndex(sf::Vector2u position) const noexcept;

		void ShrinkSizeX(uint32_t newSizeX) noexcept;
		void ExpandSizeX(uint32_t newSizeX) noexcept;

		void ShrinkSizeY(uint32_t newSizeY) noexcept;
		void ExpandSizeY(uint32_t newSizeY) noexcept;
	private:
		std::vector<uint32_t> m_TilePool;
		sf::Vector2u m_MapSize;
		float m_TileSize;

		SpriteSheet m_TileSheet;
	};
}
