#pragma once
#include "Algorithm/EvadeGrid.h"

namespace Evade
{
	inline MenuTab* main_menu{};
	inline MenuItem* enable{};

	void initialize();
	void on_unload();

	void on_tick();
	void on_draw();

	bool should_evade();
	bool is_pos_dangerous(const Vec3& pos);
	void clean_up();
	void evade();

	std::vector<EvadeGrid::Node*> find_path(const Vec3& start_pos);
}
