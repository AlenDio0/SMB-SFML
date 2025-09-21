#include "EditorState.hpp"
#include <cmath>

namespace SMB
{
	EditorState::EditorState(const SpriteSheet& tileSheet, const sf::RenderWindow& window) noexcept
		: m_TileMap(sf::Vector2u(16u, 10u), 48.f, tileSheet), m_Camera(window)
	{
	}

	void EditorState::OnEvent(const std::optional<sf::Event>& event)
	{
		if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
			m_MousePosition = mouseMoved->position;

		if (const auto* wheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
			OnMouseWheelScrolledEvent(*wheelScrolled);

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			OnKeyPressedEvent(*keyPressed);
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

	void EditorState::OnMouseWheelScrolledEvent(const sf::Event::MouseWheelScrolled& wheelScrolled) noexcept
	{
		const float ratio = (m_TileMap.GetMapSize().x + m_TileMap.GetMapSize().y) * m_TileMap.GetTileSize();
		const float minZoom = ratio / 2000.f;
		const float maxZoom = std::max(ratio / 500.f, minZoom * 2.f);

		const float zoomAmount = m_Camera.GetZoomFactor() / 10.f;

		if (wheelScrolled.delta > 0.f)
			m_Camera.ZoomIn(zoomAmount, minZoom);
		else if (wheelScrolled.delta < 0.f)
			m_Camera.ZoomOut(zoomAmount, maxZoom);
	}

	void EditorState::OnKeyPressedEvent(const sf::Event::KeyPressed& keyPressed) noexcept
	{
		const sf::Vector2u& mapSize = m_TileMap.GetMapSize();
		const float& tileSize = m_TileMap.GetTileSize();

		using Key = sf::Keyboard::Key;
		switch (keyPressed.code)
		{
		case Key::O:
			m_Camera.MoveX(-m_Camera.GetView().getCenter().x);
			m_Camera.MoveY(-m_Camera.GetView().getCenter().y);
			break;
		case Key::Q:
			m_SelectedID -= m_SelectedID != 0u;
			break;
		case Key::E:
			m_SelectedID = std::min(++m_SelectedID, m_TileMap.GetTileSheet().GetSizeID() - 1u);
			break;
		case Key::Add:
			if (keyPressed.control)
				m_TileMap.ResizeMap(mapSize + sf::Vector2u(1u, 0u));
			if (keyPressed.shift)
				m_TileMap.ResizeMap(mapSize + sf::Vector2u(0u, 1u));
			if (keyPressed.alt)
				m_TileMap.setTileSize(tileSize + 1.f);
			break;
		case Key::Subtract:
			if (keyPressed.control)
				m_TileMap.ResizeMap(mapSize - sf::Vector2u(mapSize.x != 0u, 0u));
			if (keyPressed.shift)
				m_TileMap.ResizeMap(mapSize - sf::Vector2u(0u, mapSize.y != 0u));
			if (keyPressed.alt)
				m_TileMap.setTileSize(tileSize - (tileSize >= 1.f ? 1.f : 0.f));
			break;
		}
	}

	void EditorState::HandleMousePressed() noexcept
	{
		using Button = sf::Mouse::Button;
		if (sf::Mouse::isButtonPressed(Button::Left))
			SetMouseTile(m_SelectedID);
		if (sf::Mouse::isButtonPressed(Button::Right))
			SetMouseTile(m_TileMap.GetTileSheet().GetSizeID());
	}

	void EditorState::HandleCameraMovement(float deltaTime) noexcept
	{
		float cameraSpeed = 1000.f * deltaTime * m_Camera.GetZoomFactor();
		if (cameraSpeed > 1.f)
			cameraSpeed = ceil(cameraSpeed);

		using Key = sf::Keyboard::Key;
		if (sf::Keyboard::isKeyPressed(Key::A))
			m_Camera.MoveX(-cameraSpeed);
		if (sf::Keyboard::isKeyPressed(Key::D))
			m_Camera.MoveX(cameraSpeed);
		if (sf::Keyboard::isKeyPressed(Key::W))
			m_Camera.MoveY(-cameraSpeed);
		if (sf::Keyboard::isKeyPressed(Key::S))
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
		const sf::Color fillColor = sf::Color(255, 255, 255, 80);
		const sf::Color outlineColor = sf::Color::Red;
		const float outlineThickness = -1.f;

		sf::RectangleShape tileRect = CreateRect(sf::Vector2f(size, size), position, fillColor, outlineColor, outlineThickness);
		if (auto texTileRect = m_TileMap.GetTileSheet().GetRect(m_SelectedID))
		{
			tileRect.setTexture(m_TileMap.GetTileSheet()._TexturePtr);
			tileRect.setTextureRect(texTileRect.value());
		}

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
