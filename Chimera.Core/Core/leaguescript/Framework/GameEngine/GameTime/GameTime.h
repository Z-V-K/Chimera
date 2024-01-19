#pragma once

#include "../Impl/Common/Common.h"

class GameClock final {
public:
	static float get_time();
	static int get_tick_count();

	virtual float exported_get_time();
	virtual int exported_get_tick_count();
};

extern GameClock* g_game_clock;