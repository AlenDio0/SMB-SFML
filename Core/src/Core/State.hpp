#pragma once
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Core
{
	class Application;

	class State
	{
	public:
		inline State() noexcept = default;
		inline virtual ~State() noexcept = default;

		inline virtual void OnAdd() {}
		inline virtual void OnRemove() {}

		inline virtual void OnInit() {}
		inline virtual void OnPause() {}
		inline virtual void OnResume() {}

		inline virtual void OnEvent(const std::optional<sf::Event>& event) {}
		inline virtual void OnUpdate(float deltaTime) {}
		inline virtual void OnRender(sf::RenderTarget& target) {}
	protected:
		Application& GetApp() const noexcept;

		template<typename T, typename... Args>
		inline void AddState(bool replace, Args&& ... args) noexcept
		{
			QueueState(std::move(std::make_unique<T>(std::forward<Args>(args)...)), replace);
		}
		void RemoveState() const noexcept;
	private:
		void QueueState(std::unique_ptr<State> state, bool replace) const noexcept;
	};
}
