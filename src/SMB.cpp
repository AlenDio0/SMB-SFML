#include "SMB.hpp"
#include "GameState.hpp"

namespace SMB
{
	Engine::Engine() noexcept
		: m_Window(sf::VideoMode({ 800u, 600u }), "Super Mario Bros.", sf::Style::Default)
	{
		m_Window.setVerticalSyncEnabled(true);

		m_States.AddState<GameState>(false);
	}

	void Engine::RunGame()
	{
		sf::Clock deltaClock;
		while (m_Window.isOpen())
		{
			float deltaTime = deltaClock.restart().asSeconds();

			if (!m_States.ProcessStateChanges())
			{
				m_Window.close();
				break;
			}

			while (auto event = m_Window.pollEvent())
				OnEvent(event);

			m_States.GetCurrentState().OnUpdate(deltaTime);

			OnRender();
		}
	}

	void Engine::OnEvent(const std::optional<sf::Event>& event)
	{
		if (event->is<sf::Event::Closed>())
			m_Window.close();

		m_States.GetCurrentState().OnEvent(event);
	}

	void Engine::OnRender()
	{
		m_Window.clear();
		m_States.GetCurrentState().OnRender(m_Window);
		m_Window.display();
	}
}
