#include "Application.hpp"

namespace Core
{
	Application::Application(const ApplicationSettings& appSettings) noexcept
		: m_Settings(appSettings),
		m_Window(sf::VideoMode(appSettings._WindowSize), appSettings._WindowTitle, appSettings._WindowStyle)
	{
		s_Instance = this;
	}

	Application::~Application() noexcept
	{
		s_Instance = nullptr;
	}

	void Application::Run() noexcept
	{
		m_Running = true;

		sf::Clock deltaClock;
		while (m_Window.isOpen() && m_Running)
		{
			float deltaTime = deltaClock.restart().asSeconds();

			if (!m_States.ProcessStateChanges())
			{
				Stop();
				break;
			}

			try
			{
				State& state = m_States.GetCurrentState();

				while (auto event = m_Window.pollEvent())
				{
					if (m_Settings._OnEvent)
						m_Settings._OnEvent(m_Window, event);

					state.OnEvent(event);
				}

				state.OnUpdate(deltaTime);

				m_Window.clear();
				state.OnRender(m_Window);
				m_Window.display();
			}
			catch (const std::exception&)
			{
				break;
			}
		}

		m_Window.close();
		m_States.Clear();
	}

	void Application::Stop() noexcept
	{
		m_Running = false;
	}

	sf::RenderWindow& Application::GetWindow() noexcept
	{
		return m_Window;
	}

	AssetManager& Application::GetAsset() noexcept
	{
		return m_Assets;
	}

	void Application::AddState(std::unique_ptr<State> state, bool replace) noexcept
	{
		m_States.AddState(std::move(state), replace);
	}

	void Application::RemoveState() noexcept
	{
		m_States.RemoveState();
	}

	Application& Application::Get() noexcept
	{
		assert(s_Instance);
		return *s_Instance;
	}
}
