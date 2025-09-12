#include "SMB.hpp"

namespace SMB
{
	Engine::Engine() noexcept
		: m_Window(sf::VideoMode({ 800u, 600u }), "Super Mario Bros.", sf::Style::Default)
	{
	}

	void Engine::RunGame() noexcept
	{
		while (m_Window.isOpen())
		{
			while (auto event = m_Window.pollEvent())
				OnEvent(event);

			m_Window.clear();
			m_Window.display();
		}
	}

	void Engine::OnEvent(const std::optional<sf::Event>& event) noexcept
	{
		if (event->is<sf::Event::Closed>())
			m_Window.close();
	}
}
