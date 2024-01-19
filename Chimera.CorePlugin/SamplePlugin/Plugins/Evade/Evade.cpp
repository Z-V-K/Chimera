#include "Evade.h"

#include "Algorithm/ThetaStar.h"
#include "DB/EvadeDB.h"
#include "SpellDetector/SpellDetector.h"

bool bshould_evade = false;

void Evade::initialize()
{
	EvadeDB::initialize();
	SpellDetector::initialize();

	main_menu = menu_manager->create_menu("core_evade", "Evade", ICON_FA_RUNNING);
	enable = main_menu->add_keybind("enable", "Enable", false, 'K', true);
	main_menu->set_enabled(enable);

	callbacks<EventType::OnDraw>::add_callback(on_draw, "Evade");
}

void Evade::on_unload()
{
	SpellDetector::on_unload();
	EvadeDB::on_unload();
}

void Evade::on_tick()
{

}

void Evade::on_draw()
{
	return;

	// ON_TICK
	if (!should_evade())
		return;

	evade();
	// ...
}

bool Evade::should_evade()
{
	return true;

	return enable->get_bool() && is_pos_dangerous(local_player->get_server_position());
}

bool Evade::is_pos_dangerous(const Vec3& pos)
{
	for (const auto& spell : SpellDetector::detected_spells)
	{
		if (spell->polygon.is_inside(pos))
			return true;
	}

	return false;
}

void Evade::clean_up()
{
	
}

void Evade::evade()
{
	const auto pos = local_player->get_server_position();

	const auto path = find_path(pos);

	for (const auto& node : path)
	{
		draw_manager->circle(node->center, 25.f, Color(49, 237, 96, 120), 1, true);
	}
}

std::vector<EvadeGrid::Node*> Evade::find_path(const Vec3& start_pos)
{
	const auto cursor_pos = cursor->get_world_position();

	if (!cursor_pos.is_valid())
		return { };

	EvadeGrid grid{ start_pos };

	if (!grid.place(cursor_pos))
		return { };

	grid.draw();

	return ThetaStar::run(grid,
		grid.nodes[0][0].center,
		cursor_pos,
		local_player->get_movement_speed(),
		.03 + net_client->get_ping() / 2000);
}