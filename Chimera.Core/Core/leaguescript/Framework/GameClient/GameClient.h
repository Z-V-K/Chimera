#pragma once

#include "../Impl/Common/Common.h"

namespace Enums
{
	enum class GameState : uint8_t
	{
		Loading = 0,
		Connecting = 1,
		Running = 2,
		Finished = 3
	};
}

class GameClient final
{
public:
	static GameClient* instance();
	Enums::GameState get_game_state();
};