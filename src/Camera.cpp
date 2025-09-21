#include "Camera.hpp"

namespace SMB
{
	Camera::Camera(const sf::RenderWindow& window) noexcept
		: m_WindowPtr(&window), m_Center(window.getView().getCenter())
	{
	}

	void Camera::MoveX(float offsetX) noexcept
	{
		m_Center.x += offsetX;
	}

	void Camera::MoveY(float offsetY) noexcept
	{
		m_Center.y += offsetY;
	}

	void Camera::ZoomIn(float amount, float min) noexcept
	{
		m_ZoomFactor = std::max(m_ZoomFactor - amount, min);
	}

	void Camera::ZoomOut(float amount, float max) noexcept
	{
		m_ZoomFactor = std::min(m_ZoomFactor + amount, max);
	}

	bool Camera::HasFocus() const noexcept
	{
		return m_WindowPtr->hasFocus();
	}

	sf::Vector2f Camera::GetRelativePosition(sf::Vector2i position) const noexcept
	{
		return m_WindowPtr->mapPixelToCoords(position, GetView());
	}

	float Camera::GetZoomFactor() const noexcept
	{
		return m_ZoomFactor;
	}

	sf::View Camera::GetView() const noexcept
	{
		return sf::View(m_Center, (sf::Vector2f)m_WindowPtr->getSize() * m_ZoomFactor);
	}
}
