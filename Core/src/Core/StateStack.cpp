#include "StateStack.hpp"

namespace Core
{
	void StateStack::AddState(std::unique_ptr<State> state, bool replace) noexcept
	{
		m_NewState = std::move(state);

		m_Adding = true;
		m_Removing = replace;
	}

	void StateStack::RemoveState() noexcept
	{
		m_Removing = true;
	}

	bool StateStack::ProcessStateChanges()
	{
		if (m_Removing)
			OnRemoving();

		if (m_Adding)
			OnAdding();

		return !m_States.empty();
	}

	State& StateStack::GetCurrentState() const
	{
		if (m_States.empty())
			throw std::runtime_error("Attempted to get the current State from an empty stack");

		return *m_States.top();
	}

	void StateStack::Clear() noexcept
	{
		while (!m_States.empty())
			OnRemoving();
	}

	void StateStack::OnAdding() noexcept
	{
		if (!m_NewState)
			return;

		if (!m_States.empty())
			m_States.top()->OnPause();

		m_States.push(std::move(m_NewState));
		m_States.top()->OnAdd();

		m_NewState.reset();

		m_Adding = false;
		m_Removing = false;
	}

	void StateStack::OnRemoving() noexcept
	{
		if (m_States.empty())
			return;

		m_States.pop();

		if (!m_States.empty())
			m_States.top()->OnResume();

		m_Removing = false;
	}
}
