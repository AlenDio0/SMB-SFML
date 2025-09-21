#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Core
{
	class AssetManager
	{
	public:
		AssetManager() noexcept = default;
		~AssetManager() noexcept = default;

		void LoadTexture(std::string_view key, const std::filesystem::path& path) noexcept;
		void LoadFont(std::string_view key, const std::filesystem::path& path) noexcept;
		void LoadSoundBuffer(std::string_view key, const std::filesystem::path& path) noexcept;

		const sf::Texture& GetTexture(std::string_view key) const;
		const sf::Font& GetFont(std::string_view key) const;
		const sf::SoundBuffer& GetSoundBuffer(std::string_view key) const;
	private:
		std::unordered_map<std::string_view, sf::Texture> m_Textures;
		std::unordered_map<std::string_view, sf::Font> m_Fonts;
		std::unordered_map<std::string_view, sf::SoundBuffer> m_SoundBuffers;
	};
}
