#pragma once
#include "State.hpp"
#include <stack>
#include <memory>

namespace Core
{
	class StateStack
	{
	public:
		void AddState(std::unique_ptr<State> state, bool replace) noexcept;
		void RemoveState() noexcept;

		bool ProcessStateChanges();

		State& GetCurrentState() const;

		void Clear() noexcept;
	private:
		void OnAdding() noexcept;
		void OnRemoving() noexcept;
	private:
		std::stack<std::unique_ptr<State>> m_States;

		std::unique_ptr<State> m_NewState;
		bool m_Adding = false;
		bool m_Removing = false;
	};
}
