#pragma once
#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace Core
{
	class State
	{
	public:
		struct Request
		{
			std::unique_ptr<State> _NewState;

			bool _Add = false;
			bool _Replace = false;
			bool _Remove = false;
		};
	public:
		State() noexcept = default;
		virtual ~State() noexcept = default;

		inline virtual void OnInit() {}
		inline virtual void OnPause() {}
		inline virtual void OnResume() {}

		inline virtual void OnEvent(const std::optional<sf::Event>& event) {}
		inline virtual void OnUpdate(float deltaTime) {}
		inline virtual void OnRender(sf::RenderTarget& target) {}

		inline bool HasRequest() const noexcept { return m_Request._Add || m_Request._Remove; }
		inline Request& GetRequest() noexcept { return m_Request; }
		inline void ResetRequest() noexcept { m_Request = Request{}; }
	protected:
		template<typename S, typename... Args>
		inline void AddState(bool replace, Args&& ... args) noexcept
		{
			m_Request._NewState = std::make_unique<S>(std::forward<Args>(args)...);

			m_Request._Add = true;
			m_Request._Replace = replace;
		}

		inline void RemoveState() noexcept
		{
			m_Request._Remove = true;
		}
	private:
		Request m_Request;
	};
}
