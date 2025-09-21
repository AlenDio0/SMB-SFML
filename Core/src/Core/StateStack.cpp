#include "StateStack.hpp"

namespace Core
{
	StateStack::~StateStack() noexcept
	{
		Clear();
	}

	void StateStack::Clear() noexcept
	{
		while (!m_Stack.empty())
			m_Stack.pop();
	}

	State& StateStack::GetCurrentState() const
	{
		if (m_Stack.empty())
			throw std::runtime_error("Attempted to get the current State from an empty stack");

		return *m_Stack.top().get();
	}

	void StateStack::AddState(std::unique_ptr<State> state, bool replace) noexcept
	{
		m_CurrentRequest._NewState.swap(state);

		m_CurrentRequest._Add = true;
		m_CurrentRequest._Replace = replace;
	}

	void StateStack::RemoveState() noexcept
	{
		m_CurrentRequest._Remove = true;
	}

	bool StateStack::ProcessStateChanges() noexcept
	{
		CheckStateRequest();

		if (m_CurrentRequest._Remove)
			OnRemoving();

		if (m_CurrentRequest._Add)
			OnAdding();

		return !m_Stack.empty();
	}

	void StateStack::CheckStateRequest()
	{
		if (!m_Stack.empty() && m_Stack.top()->HasRequest())
		{
			m_CurrentRequest = std::move(m_Stack.top()->GetRequest());
			m_Stack.top()->ResetRequest();
		}
	}

	void StateStack::OnAdding()
	{
		if (!m_CurrentRequest._NewState)
			throw std::runtime_error("Attempted to process a nullptr State");

		if (!m_Stack.empty())
		{
			if (m_CurrentRequest._Replace)
				m_Stack.pop();
			else
				m_Stack.top()->OnPause();
		}

		m_Stack.push(std::move(m_CurrentRequest._NewState));

		m_CurrentRequest._Add = false;
		m_CurrentRequest._Replace = false;
	}

	void StateStack::OnRemoving()
	{
		if (m_Stack.empty())
			throw std::runtime_error("Attempted to remove on an empty stack");

		m_Stack.pop();

		if (!m_Stack.empty())
			m_Stack.top()->OnResume();

		m_CurrentRequest._Remove = false;
	}
}
