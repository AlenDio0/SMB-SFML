#include "Application.hpp"

namespace Core
{
	Application::Application(sf::Vector2u windowSize, const sf::String& windowTitle) noexcept
		: m_Window(sf::VideoMode(windowSize), windowTitle, sf::Style::Default)
	{
	}

	void Application::OnEvent(const std::optional<sf::Event>& event)
	{
	}

	void Application::Run()
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
			State& currentState = m_States.GetCurrentState();

			while (auto event = m_Window.pollEvent())
			{
				OnEvent(event);
				m_States.GetCurrentState().OnEvent(event);
			}

			m_States.GetCurrentState().OnUpdate(deltaTime);

			m_Window.clear();
			m_States.GetCurrentState().OnRender(m_Window);
			m_Window.display();
		}
	}
}
