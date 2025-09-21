#include "AppSMB.hpp"
#include "EditorState.hpp"

namespace SMB
{
	AppSMB::AppSMB() noexcept
		: Application(sf::Vector2u(800u, 600u), "Super Mario Bros. - SFML")
	{
		m_Window.setVerticalSyncEnabled(true);

		m_Assets.LoadTexture("tiles", "assets/tiles.png");

		Core::SpriteSheet tileSheet(m_Assets.GetTexture("tiles"), sf::Vector2u(2u, 1u), sf::Vector2u(16u, 16u));
		m_States.AddState<EditorState>(false, tileSheet, m_Window);
	}

	void AppSMB::OnEvent(const std::optional<sf::Event>& event)
	{
		if (event->is<sf::Event::Closed>())
			m_Window.close();

		if (const auto* resizedEvent = event->getIf<sf::Event::Resized>())
		{
			sf::View view = m_Window.getView();
			view.setSize((sf::Vector2f)resizedEvent->size);
			m_Window.setView(view);
		}
	}
}
