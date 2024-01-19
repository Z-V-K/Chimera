#include "RangeIndicator.h"
#include "../Awareness.h"

void Awareness::RangeIndicator::on_draw()
{
	if (Menu::attack_range_indicator->get_bool())
	{
		if (local_player->is_alive() && local_player->is_visible() && local_player->is_visible_on_screen())
		{
			draw_manager->circle(
				local_player->get_position(),
				local_player->get_attack_range(),
				Menu::attack_range_indicator_color->get_color(),
				(float)(Menu::attack_range_thickness->get_int()),
				true
			);
		}
	}

	if (Menu::enemy_turret_range_indicator->get_bool())
	{
		for (const auto& turret : entities->get_enemy_turrets())
		{
			if (turret && turret->is_alive() && turret->is_visible() && turret->is_visible_on_screen() && turret->is_targetable())
			{
				draw_manager->circle(
					turret->get_position() + 7.0f,
					local_player->get_bounding_radius() + 810.0f,
					Menu::enemy_turret_range_indicator_color->get_color(),
					(float)(Menu::enemy_turret_range_thickness->get_int()),
					true
				);
			}
		}
	}

	for (const auto& hero : entities->get_heroes())
	{
		if (hero && hero->is_alive() && hero->is_visible() && hero->is_visible_on_screen())
		{
			if (hero->is_enemy() && Menu::enemy_range_indicator->get_bool())
				draw_manager->circle(
					hero->get_position(),
					hero->get_attack_range(),
					Menu::enemy_range_indicator_color->get_color(),
					(float)(Menu::enemy_range_thickness->get_int()),
					true
				);

			if (hero->is_ally() && hero != local_player && Menu::ally_range_indicator->get_bool())
				draw_manager->circle(
					hero->get_position(),
					hero->get_attack_range(),
					Menu::ally_range_indicator_color->get_color(),
					(float)(Menu::ally_range_thickness->get_int()),
					true
				);
		}
	}
}

void Awareness::RangeIndicator::initialize()
{
	Color purple =	{ 102,  0,  178,  40 };
	Color red =		{  230,  0,  0,  40 };
	Color green =	{  0,  230,  0,  40 };
	Color blue =	{ 170, 216, 232,  40 };

	Menu::attack_range_group = Awareness::Menu::tab_range_indicator->add_menu("attackRangeIndicatorGroup", "Attack Range Indicator");
	Menu::attack_range_indicator = Menu::attack_range_group->add_checkbox("attack_range_indicator", "Draw", true);
	Menu::attack_range_indicator_color = Menu::attack_range_group->add_colorpick("attack_range_indicator_color", "Color", purple);
	Menu::attack_range_thickness = Menu::attack_range_group->add_slider("attack_range_thickness", "Thickness", 3, 1, 5);

	Menu::attack_range_group->set_enabled(Menu::attack_range_indicator);

	Menu::ally_range_group = Awareness::Menu::tab_range_indicator->add_menu("allypRangeIndicatorGroup", "Ally Range Indicator");
	Menu::ally_range_indicator = Menu::ally_range_group->add_checkbox("ally_range_indicator", "Draw", true);
	Menu::ally_range_indicator_color = Menu::ally_range_group->add_colorpick("ally_range_indicator_color", "Color", blue);
	Menu::ally_range_thickness = Menu::ally_range_group->add_slider("ally_range_thickness", "Thickness", 3, 1, 5);

	Menu::ally_range_group->set_enabled(Menu::ally_range_indicator);

	Menu::enemy_turret_range_group = Awareness::Menu::tab_range_indicator->add_menu("enemyTurretRangeIndicatorGroup", "Enemy Turret Range Indicator");
	Menu::enemy_turret_range_indicator = Menu::enemy_turret_range_group->add_checkbox("turretRangeIndicator", "Draw", true);
	Menu::enemy_turret_range_indicator_color = Menu::enemy_turret_range_group->add_colorpick("turretRangeIndicatorColor", "Color", red);
	Menu::enemy_turret_range_thickness = Menu::enemy_turret_range_group->add_slider("turretRangeThickness", "Thickness", 3, 1, 5);

	Menu::enemy_turret_range_group->set_enabled(Menu::enemy_turret_range_indicator);

	Menu::enemy_range_group = Awareness::Menu::tab_range_indicator->add_menu("enemyRangeIndicatorGroup", "Enemy Range Indicator");
	Menu::enemy_range_indicator = Menu::enemy_range_group->add_checkbox("enemy_range_indicator", "Draw", true);
	Menu::enemy_range_indicator_color = Menu::enemy_range_group->add_colorpick("enemy_range_indicator_color", "Color", red);
	Menu::enemy_range_thickness = Menu::enemy_range_group->add_slider("enemy_range_thickness", "Thickness", 3, 1, 5);

	Menu::enemy_range_group->set_enabled(Menu::enemy_range_indicator);

	callbacks<EventType::OnDrawEnvironment>::add_callback(on_draw, "RangeIndicator");
}