#pragma once

#include "../SDK/LUA/LuaIncludes.h"

struct DelayedAction
{
	int time = 0;
	std::function<void()> fn = nullptr;
	luabridge::LuaRef fn_lua = nullptr;
};

class Scheduler final
{
private:
	std::vector<DelayedAction> action_list{ };
	std::vector<DelayedAction> action_list_lua{ };
public:
	virtual void delay_action(int delay_ticks, const std::function<void()> fn);
	void delay_action(int delay_ticks, const luabridge::LuaRef ref);
	void on_update();
	void clear();
};

extern Scheduler* g_scheduler;