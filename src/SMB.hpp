#include <SFML/Graphics.hpp>

namespace SMB
{
	class Engine
	{
	public:
		Engine() noexcept;

		void RunGame() noexcept;
	private:
		void OnEvent(const std::optional<sf::Event>& event) noexcept;
	private:
		sf::RenderWindow m_Window;
	};
}
