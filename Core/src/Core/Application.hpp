#pragma once
#include <SFML/Graphics.hpp>
#include "StateStack.hpp"
#include "AssetManager.hpp"

namespace Core
{
	class Application
	{
	public:
		Application(sf::Vector2u windowSize, const sf::String& windowTitle) noexcept;
		virtual ~Application() noexcept = default;

		virtual void OnEvent(const std::optional<sf::Event>& event);

		void Run();
	protected:
		sf::RenderWindow m_Window;
		StateStack m_States;
		AssetManager m_Assets;
	};
}
