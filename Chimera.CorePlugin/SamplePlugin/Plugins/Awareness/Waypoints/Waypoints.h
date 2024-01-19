#pragma once

namespace Awareness::Waypoints
{
	namespace Menu 
	{
		inline MenuTab* local_player{};
		inline MenuItem* my_waypoints;
		inline MenuItem* my_waypoints_point_col;
		inline MenuItem* my_waypoints_line_col;

		inline MenuTab* enemies{};
		inline MenuItem* enemy_waypoints;
		inline MenuItem* enemy_waypoints_point_col;
		inline MenuItem* enemy_waypoints_line_col;

		inline MenuTab* allys{};
		inline MenuItem* ally_waypoints;
		inline MenuItem* ally_waypoints_point_col;
		inline MenuItem* ally_waypoints_line_col;

		inline MenuItem* my_clones_waypoints{};
		inline MenuItem* ally_clones_waypoints{};
		inline MenuItem* enemy_clones_waypoints{};
	}

	static void on_draw();
	static void draw_waypoints(GameObject* entity, const uint32_t& col_point, const uint32_t& col_line);

	void initialize();
};

