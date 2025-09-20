#pragma once
#include <SFML/Graphics.hpp>
#include "StateStack.hpp"
#include "AssetManager.hpp"

namespace SMB
{
	class Engine
	{
	public:
		Engine() noexcept;
		~Engine() noexcept = default;

		void RunGame();
	private:
		void OnEvent(const std::optional<sf::Event>& event);
		void OnRender();
	private:
		sf::RenderWindow m_Window;
		StateStack m_States;
		AssetManager m_Assets;
	};
}
