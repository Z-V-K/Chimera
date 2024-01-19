#include "Scheduler.h"

#include "../Framework/GameEngine/GameTime/GameTime.h"

Scheduler* g_scheduler = new Scheduler();

void Scheduler::delay_action(int delay_ticks, const std::function<void()> fn)
{
	if (!fn || delay_ticks == 0)
		return;

	action_list.push_back({ GameClock::get_tick_count() + delay_ticks, fn });
}

void Scheduler::delay_action(int delay_ticks, const luabridge::LuaRef ref)
{
	if (!ref || delay_ticks == 0)
		return;

	action_list.push_back({ GameClock::get_tick_count() + delay_ticks, nullptr, ref });
}

void Scheduler::on_update()
{
	for (auto it = action_list.begin(); it != action_list.end();)
	{
		if (it->time <= GameClock::get_tick_count())
		{
			if (it->fn)
				it->fn();
			if (it->fn_lua)
				it->fn_lua();
			
			it = action_list.erase(it);
		}
		else ++it;
	}
}

void Scheduler::clear()
{
	action_list.clear();
}