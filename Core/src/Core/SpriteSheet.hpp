#pragma once
#include "SpriteBank.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
#include <filesystem>

namespace Core
{
	class AssetManager;

	class SpriteSheet
	{
	public:
		SpriteSheet() noexcept = default;
		SpriteSheet(const std::filesystem::path& path, const AssetManager& assets);
		SpriteSheet(const sf::Texture& texture, sf::Vector2u size, sf::Vector2u spriteSize, const SpriteBank& sprites = {}) noexcept;
		~SpriteSheet() noexcept = default;

		uint32_t GetSizeID() const noexcept;

		std::optional<sf::IntRect> GetRect(std::string_view key) const noexcept;
		std::optional<sf::IntRect> GetRect(uint32_t id) const noexcept;
		std::optional<sf::IntRect> GetRect(sf::Vector2i position) const noexcept;
	public:
		const sf::Texture* _TexturePtr = nullptr;

		const sf::Vector2u _Size;
		const sf::Vector2u _SpriteSize;
	private:
		static SpriteSheet LoadFromFile(const std::filesystem::path& path, const AssetManager& assets);
	private:
		SpriteBank m_Sprites;
	};
}
