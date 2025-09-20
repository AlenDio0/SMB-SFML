#pragma once
#include "State.hpp"
#include "TileMap.hpp"

namespace SMB
{
	class GameState : public State
	{
	public:
		GameState() noexcept;
		virtual ~GameState() noexcept = default;
	};
}
