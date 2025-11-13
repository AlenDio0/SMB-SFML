#include "State.hpp"
#include "Application.hpp"

namespace Core
{
	Application& State::GetApp() const noexcept
	{
		return Application::Get();
	}

	void State::RemoveState() const noexcept
	{
		Application::Get().RemoveState();
	}

	void State::QueueState(std::unique_ptr<State> state, bool replace) const noexcept
	{
		Application::Get().AddState(std::move(state), replace);
	}
}
