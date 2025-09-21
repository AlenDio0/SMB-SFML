#include "EditorState.hpp"
#include <cmath>

namespace SMB
{
	EditorState::EditorState(const SpriteSheet& tileSheet, const sf::RenderWindow& window) noexcept
		: m_TileMap(tileSheet, sf::Vector2u(16u, 10u), 48.f), m_TileSheet(tileSheet), m_Camera(window)
	{
	}

	void EditorState::OnEvent(const std::optional<sf::Event>& event)
	{
		if (const auto* mouseEvent = event->getIf<sf::Event::MouseMoved>())
			m_MousePosition = mouseEvent->position;

		if (const auto* wheelEvent = event->getIf<sf::Event::MouseWheelScrolled>())
		{
			const float zoomAmount = 0.2f;
			const float maxZoom = 4.f;

			if (wheelEvent->delta > 0.f)
				m_Camera.ZoomIn(zoomAmount, zoomAmount);
			else if (wheelEvent->delta < 0.f)
				m_Camera.ZoomOut(zoomAmount, maxZoom);
		}
	}

	void EditorState::OnUpdate(float deltaTime)
	{
		if (!m_Camera.HasFocus())
			return;

		HandleMousePressed();
		HandleCameraMovement(deltaTime);
	}

	void EditorState::OnRender(sf::RenderTarget& target)
	{
		target.setView(m_Camera.GetView());

		m_TileMap.Render(target);
		RenderMapBorder(target);

		RenderMouseTile(target);
	}

	void EditorState::HandleMousePressed() noexcept
	{
		using Button = sf::Mouse::Button;
		if (sf::Mouse::isButtonPressed(Button::Left))
			SetMouseTile(0u);
		else if (sf::Mouse::isButtonPressed(Button::Right))
			SetMouseTile(1u);
	}

	void EditorState::HandleCameraMovement(float deltaTime) noexcept
	{
		const float cameraSpeed = floor(1000.f * deltaTime * m_Camera.GetZoomFactor());

		using Key = sf::Keyboard::Key;
		if (sf::Keyboard::isKeyPressed(Key::A))
			m_Camera.MoveX(-cameraSpeed);
		else if (sf::Keyboard::isKeyPressed(Key::D))
			m_Camera.MoveX(cameraSpeed);
		if (sf::Keyboard::isKeyPressed(Key::W))
			m_Camera.MoveY(-cameraSpeed);
		else if (sf::Keyboard::isKeyPressed(Key::S))
			m_Camera.MoveY(cameraSpeed);
	}

	void EditorState::RenderMapBorder(sf::RenderTarget& target) const noexcept
	{
		const sf::Vector2f size = (sf::Vector2f)m_TileMap.GetMapSize() * m_TileMap.GetTileSize();
		const sf::Color fillColor = sf::Color::Transparent;
		const sf::Color outlineColor = sf::Color::White;
		const float outlineThickness = 1.f;

		sf::RectangleShape borderRect = CreateRect(size, {}, fillColor, outlineColor, outlineThickness);
		target.draw(borderRect);
	}

	void EditorState::RenderMouseTile(sf::RenderTarget& target) const noexcept
	{
		auto tilePosition = GetMouseTilePosition();
		if (!tilePosition.has_value())
			return;

		const float size = m_TileMap.GetTileSize();
		const sf::Vector2f position = (sf::Vector2f)tilePosition.value() * size;
		const sf::Color fillColor = sf::Color(255, 0, 0, 16);
		const sf::Color outlineColor = sf::Color::Red;
		const float outlineThickness = -1.f;

		sf::RectangleShape tileRect = CreateRect(sf::Vector2f(size, size), position, fillColor, outlineColor, outlineThickness);
		target.draw(tileRect);
	}

	void EditorState::SetMouseTile(uint32_t id) noexcept
	{
		auto tilePosition = GetMouseTilePosition();
		if (!tilePosition.has_value())
			return;

		m_TileMap.SetTile(tilePosition.value(), id);
	}

	std::optional<sf::Vector2u> EditorState::GetMouseTilePosition() const noexcept
	{
		sf::Vector2f position = m_Camera.GetRelativePosition(m_MousePosition);
		const sf::Vector2f size = (sf::Vector2f)m_TileMap.GetMapSize() * m_TileMap.GetTileSize();
		if (position.x < 0.f || position.x > size.x || position.y < 0.f || position.y > size.y)
			return std::nullopt;

		return (sf::Vector2u)(position / m_TileMap.GetTileSize());
	}

	sf::RectangleShape EditorState::CreateRect(sf::Vector2f size, sf::Vector2f position, sf::Color fillColor, sf::Color outlineColor, float thickness) const noexcept
	{
		sf::RectangleShape shape(size);
		shape.setPosition(position);
		shape.setFillColor(fillColor);
		shape.setOutlineColor(outlineColor);
		shape.setOutlineThickness(thickness * (1.f + m_Camera.GetZoomFactor()));

		return shape;
	}
}
