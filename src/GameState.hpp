#pragma once
#include "State.hpp"

namespace SMB
{
	class GameState : public State
	{
	public:
		GameState() noexcept = default;
		virtual ~GameState() noexcept = default;
	private:
	};
}
