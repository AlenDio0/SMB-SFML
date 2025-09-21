#pragma once
#include "Core/State.hpp"

namespace SMB
{
	class GameState : public Core::State
	{
	public:
		GameState() noexcept;
		virtual ~GameState() noexcept = default;
	};
}
