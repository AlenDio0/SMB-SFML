#pragma once
#include <SFML/Graphics.hpp>

namespace SMB
{
	class Camera
	{
	public:
		Camera(const sf::RenderWindow& window) noexcept;
		~Camera() noexcept = default;;

		void MoveX(float offsetX) noexcept;
		void MoveY(float offsetY) noexcept;

		void ZoomIn(float amount, float min) noexcept;
		void ZoomOut(float amount, float max) noexcept;

		bool HasFocus() const noexcept;

		sf::Vector2f GetRelativePosition(sf::Vector2i position) const noexcept;

		float GetZoomFactor() const noexcept;
		sf::View GetView() const noexcept;
	private:
		sf::Vector2f m_Center;
		float m_ZoomFactor = 1.f;

		const sf::RenderWindow* m_WindowPtr;
	};
}
