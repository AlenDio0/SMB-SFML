#pragma once
#include "State.hpp"

namespace SMB
{
	class GameState : public State
	{
	public:
		GameState() noexcept;
		virtual ~GameState() noexcept = default;
	};
}
