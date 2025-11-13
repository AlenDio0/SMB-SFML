#include "Core/Application.hpp"
#include "EditorState.hpp"

static void OnEvent(sf::RenderWindow& window, const std::optional<sf::Event>& event) noexcept
{
	if (event->is<sf::Event::Closed>())
		window.close();

	if (const auto* resizedEvent = event->getIf<sf::Event::Resized>())
	{
		sf::View view = window.getView();
		view.setSize((sf::Vector2f)resizedEvent->size);
		window.setView(view);
	}
}

int main(int argc, char* argv[])
{
	Core::ApplicationSettings appSettings;
	appSettings._WindowSize = { 800u, 600u };
	appSettings._WindowTitle = "Super Mario Bros.";
	appSettings._OnEvent = &OnEvent;

	Core::Application application(appSettings);

	auto& assets = application.GetAsset();
	assets.LoadTexture("Tile", "assets/tiles.png");
	assets.LoadSheet("Tile", "data/tiles.sheet");

	application.AddState<SMB::EditorState>(false, assets.GetSheet("Tile"));
	application.Run();

	return 0;
}