#include "Waypoints.h"

#include "../Awareness.h"

void Awareness::Waypoints::initialize()
{
	Color red{ 230, 0, 0, 125 };
	Color green{ 0, 230, 0, 125 };
	Color blue{ 170, 216, 232, 230 };
	Color white{ 255, 255, 255, 125 };

	Menu::local_player = Awareness::Menu::tab_waypoints->add_menu("local_player", "Local player");
	Menu::allys = Awareness::Menu::tab_waypoints->add_menu("allies", "Allies");
	Menu::enemies = Awareness::Menu::tab_waypoints->add_menu("enemies", "Enemies");

	Menu::my_waypoints = Menu::local_player->add_checkbox("myWaypoints", "Draw", false);
	Menu::my_clones_waypoints = Menu::local_player->add_checkbox("myCloneWaypoints", "Clones", false);
	Menu::my_waypoints_line_col = Menu::local_player->add_colorpick("myWayPointsLineCol", "Line Colour", white);
	Menu::my_waypoints_point_col = Menu::local_player->add_colorpick("myWayPointsPointCol", "Waypoint Colour", blue);

	Menu::local_player->set_enabled(Menu::my_waypoints);

	Menu::ally_waypoints = Menu::allys->add_checkbox("allyWaypoints", "Draw", false);
	Menu::ally_clones_waypoints = Menu::allys->add_checkbox("allyCloneWaypoints", "Clones", true);
	Menu::ally_waypoints_line_col = Menu::allys->add_colorpick("allyWayPointsLineCol", "Line Colour", white);
	Menu::ally_waypoints_point_col = Menu::allys->add_colorpick("allyWayPointsPointCol", "Waypoint Colour", green);

	Menu::allys->set_enabled(Menu::ally_waypoints);

	Menu::enemy_waypoints = Menu::enemies->add_checkbox("enemyWaypoints", "Draw", false);
	Menu::enemy_clones_waypoints = Menu::enemies->add_checkbox("enemyCloneWaypoints", "Clones", true);
	Menu::enemy_waypoints_line_col = Menu::enemies->add_colorpick("ememyWayPointsLineCol", "Line Colour", white);
	Menu::enemy_waypoints_point_col = Menu::enemies->add_colorpick("enemyWayPointsPointCol", "Waypoint Colour", red);

	Menu::enemies->set_enabled(Menu::enemy_waypoints);

	callbacks<EventType::OnDrawEnvironment>::add_callback(on_draw, "Waypoints");
}

void Awareness::Waypoints::on_draw()
{
	if (Menu::my_waypoints->get_bool())
	{
		if (local_player && local_player->is_alive() && local_player->is_visible() && local_player->is_visible_on_screen())
		{
			draw_waypoints(local_player, Menu::my_waypoints_point_col->get_color(), Menu::my_waypoints_line_col->get_color());
		}
	}

	for (const auto& hero : entities->get_heroes())
	{
		if (hero && hero->is_alive() && hero->is_visible() && hero->is_visible_on_screen() && hero != local_player)
		{
			if (hero->is_ally() && Menu::ally_waypoints->get_bool())
				draw_waypoints(hero, Menu::ally_waypoints_point_col->get_color(), Menu::ally_waypoints_line_col->get_color());
			if (hero->is_enemy() && Menu::enemy_waypoints->get_bool())
				draw_waypoints(hero, Menu::enemy_waypoints_point_col->get_color(), Menu::enemy_waypoints_line_col->get_color());
		}
	}

	for (const auto& clone : entities->get_clones())
	{
		if (clone && clone->is_alive() && clone->is_visible() && clone->is_visible_on_screen() )
		{
			if (clone->get_character_hash() == local_player->get_character_hash() && Menu::my_clones_waypoints->get_bool())
				draw_waypoints(clone, Menu::my_waypoints_point_col->get_color(), Menu::my_waypoints_line_col->get_color());

			if (clone->is_enemy() && Menu::enemy_clones_waypoints->get_bool())
				draw_waypoints(clone, Menu::enemy_waypoints_point_col->get_color(), Menu::enemy_waypoints_line_col->get_color());

			if (clone->is_ally() && Menu::ally_clones_waypoints->get_bool())
				draw_waypoints(clone, Menu::ally_waypoints_point_col->get_color(), Menu::ally_waypoints_line_col->get_color());
		}
	}
}

void Awareness::Waypoints::draw_waypoints(GameObject* entity, const uint32_t& col_point, const uint32_t& col_line)
{
	std::vector<Vec3> waypoints{ entity->get_path_controller_common()->get_path() };

	waypoints.insert(waypoints.begin(), entity->get_position());

	for (size_t i{ 1 }; i < waypoints.size(); i++)
	{
		draw_manager->circle(waypoints[i - 1], 10.0f, col_point, 1, true);
		draw_manager->line(waypoints[i - 1], waypoints[i], col_line, 1.5f);

		if(i == waypoints.size() - 1)
			draw_manager->circle(waypoints[waypoints.size() - 1], 10.0f, col_point, 1, true);
	}
}