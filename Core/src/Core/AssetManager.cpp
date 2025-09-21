#include "AssetManager.hpp"

namespace SMB
{
	void AssetManager::LoadTexture(std::string_view key, const std::filesystem::path& path) noexcept
	{
		sf::Texture texture;
		if (texture.loadFromFile(path))
			m_Textures.emplace(key, std::move(texture));
	}

	void AssetManager::LoadFont(std::string_view key, const std::filesystem::path& path) noexcept
	{
		sf::Font font;
		if (font.openFromFile(path))
			m_Fonts.emplace(key, std::move(font));
	}

	void AssetManager::LoadSoundBuffer(std::string_view key, const std::filesystem::path& path) noexcept
	{
		sf::SoundBuffer soundBuffer;
		if (soundBuffer.loadFromFile(path))
			m_SoundBuffers.emplace(key, std::move(soundBuffer));
	}

	const sf::Texture& AssetManager::GetTexture(std::string_view key) const
	{
		if (!m_Textures.contains(key))
			throw std::runtime_error("Texture not found: " + std::string(key));

		return m_Textures.at(key);
	}

	const sf::Font& AssetManager::GetFont(std::string_view key) const
	{
		if (!m_Fonts.contains(key))
			throw std::runtime_error("Font not found: " + std::string(key));

		return m_Fonts.at(key);
	}

	const sf::SoundBuffer& AssetManager::GetSoundBuffer(std::string_view key) const
	{
		if (!m_SoundBuffers.contains(key))
			throw std::runtime_error("SoundBuffer not found: " + std::string(key));

		return m_SoundBuffers.at(key);
	}
}