#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include "StateStack.hpp"
#include "AssetManager.hpp"

namespace Core
{
	struct ApplicationSettings
	{
		std::string _WindowTitle = "Application";
		sf::Vector2u _WindowSize = { 800u, 800u };
		uint32_t _WindowStyle = sf::Style::Default;

		std::function<void(sf::RenderWindow&, const std::optional<sf::Event>&)> _OnEvent = nullptr;
	};

	class Application
	{
	public:
		Application(const ApplicationSettings& appSettings) noexcept;
		virtual ~Application() noexcept;

		void Run() noexcept;
		void Stop() noexcept;

		sf::RenderWindow& GetWindow() noexcept;
		AssetManager& GetAsset() noexcept;

		template<std::derived_from<State> T, typename... Args>
		inline void AddState(bool replace, Args&&... args) noexcept
		{
			AddState(std::move(std::make_unique<T>(std::forward<Args>(args)...)), replace);
		}

		void AddState(std::unique_ptr<State> state, bool replace) noexcept;
		void RemoveState() noexcept;

		static Application& Get() noexcept;
	private:
		ApplicationSettings m_Settings;

		sf::RenderWindow m_Window;
		AssetManager m_Assets;
		StateStack m_States;

		bool m_Running = false;
	private:
		static inline Application* s_Instance = nullptr;
	};
}
