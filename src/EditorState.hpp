#pragma once
#include "State.hpp"
#include "TileMap.hpp"
#include "SpriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <optional>
#include "Camera.hpp"

namespace SMB
{
	class EditorState : public State
	{
	public:
		EditorState(const SpriteSheet& tileSheet, const sf::RenderWindow& window) noexcept;
		~EditorState() noexcept = default;

		virtual void OnEvent(const std::optional<sf::Event>& event) override;
		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRender(sf::RenderTarget& target) override;
	private:
		void HandleMousePressed() noexcept;
		void HandleCameraMovement(float deltaTime) noexcept;

		void RenderMapBorder(sf::RenderTarget& target) const noexcept;
		void RenderMouseTile(sf::RenderTarget& target) const noexcept;

		void SetMouseTile(uint32_t id) noexcept;

		std::optional<sf::Vector2u> GetMouseTilePosition() const noexcept;
	private:
		sf::RectangleShape CreateRect(sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness) const noexcept;
	private:
		TileMap m_TileMap;
		SpriteSheet m_TileSheet;

		uint32_t m_CurrentID = 0u;

		Camera m_Camera;
		sf::Vector2i m_MousePosition;
	};
}
