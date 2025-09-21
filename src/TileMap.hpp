#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteSheet.hpp"
#include <vector>

namespace SMB
{
	class TileMap
	{
	public:
		TileMap(SpriteSheet tileSheet, sf::Vector2u mapSize, float tileSize) noexcept;
		~TileMap() noexcept = default;

		sf::Vector2u GetMapSize() const noexcept;
		float GetTileSize() const noexcept;

		void SetTile(sf::Vector2u position, uint32_t id) noexcept;
		uint32_t GetTile(sf::Vector2u position) const noexcept;

		void Render(sf::RenderTarget& target) const noexcept;
	private:
		uint32_t GetIndex(sf::Vector2u position) const noexcept;
	private:
		std::vector<uint32_t> m_Tiles;

		SpriteSheet m_TileSheet;

		const sf::Vector2u m_MapSize;
		const float m_TileSize;
	};
}
