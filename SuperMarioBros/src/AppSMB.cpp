#include "AppSMB.hpp"
#include "EditorState.hpp"

namespace SMB
{
	AppSMB::AppSMB() noexcept
		: Application(sf::Vector2u(800u, 600u), "Super Mario Bros. - SFML")
	{
		m_Window.setVerticalSyncEnabled(true);

		m_Assets.LoadTexture("Tile", "assets/tiles.png");
		m_Assets.LoadSheet("Tile", "data/tiles.sheet");

		m_States.AddState<EditorState>(false, m_Assets.GetSheet("Tile"), m_Window);
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
