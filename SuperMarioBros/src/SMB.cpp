#include "SMB.hpp"
#include "EditorState.hpp"

namespace SMB
{
	Engine::Engine() noexcept
		: m_Window(sf::VideoMode({ 800u, 600u }), "Super Mario Bros.", sf::Style::Default)
	{
		m_Window.setVerticalSyncEnabled(true);

		m_Assets.LoadTexture("tiles", "assets/tiles.png");

		SpriteSheet tileSheet(m_Assets.GetTexture("tiles"), sf::Vector2u(2u, 1u), sf::Vector2u(16u, 16u));
		m_States.AddState<EditorState>(false, tileSheet, m_Window);
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

		if (const auto* resizedEvent = event->getIf<sf::Event::Resized>())
		{
			sf::View view = m_Window.getView();
			view.setSize((sf::Vector2f)resizedEvent->size);
			m_Window.setView(view);
		}

		m_States.GetCurrentState().OnEvent(event);
	}

	void Engine::OnRender()
	{
		m_Window.clear();
		m_States.GetCurrentState().OnRender(m_Window);
		m_Window.display();
	}
}
