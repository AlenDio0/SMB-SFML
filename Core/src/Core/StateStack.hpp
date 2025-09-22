#pragma once
#include "State.hpp"
#include <stack>
#include <memory>

namespace Core
{
	class StateStack
	{
	public:
		StateStack() noexcept = default;
		~StateStack() noexcept;

		void Clear() noexcept;

		State& GetCurrentState() const;

		void AddState(std::unique_ptr<State> state, bool replace) noexcept;
		void RemoveState() noexcept;

		template<typename S, typename... Args>
		void AddState(bool replace, Args&& ... args) noexcept
		{
			AddState(std::make_unique<S>(std::forward<Args>(args)...), replace);
		}

		bool ProcessStateChanges();
	private:
		void CheckStateRequest();
		void OnAdding();
		void OnRemoving();
	private:
		std::stack<std::unique_ptr<State>> m_Stack;

		State::Request m_CurrentRequest;
	};
}
