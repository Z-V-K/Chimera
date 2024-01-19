#include "StasisTracker.h"

uint32_t zhonya_buff_hash		= hash_fnv1a("ZhonyasRingShield");
uint32_t bardr_stasis_buff_hash = hash_fnv1a("bardrstasis");
std::unordered_map<GameObject*, float> stasis_map;

void Awareness::StasisTracker::initialize()
{
	Menu::spell_tracker_myself = Awareness::Menu::tab_stasis_tracker->add_checkbox("enableStasisTrackerMyself", "Myself", true);
	Menu::spell_tracker_allies = Awareness::Menu::tab_stasis_tracker->add_checkbox("enableStasisTrackerAlly", "Allies", true);
	Menu::spell_tracker_enemies = Awareness::Menu::tab_stasis_tracker->add_checkbox("enableStasisTrackerEnemy", "Enemies", true);

	for (const auto& hero : entities->get_heroes())
	{
		if (!hero) continue;

		stasis_map.emplace(hero, 0.0f);
	}

	callbacks<EventType::OnDraw>::add_callback(on_draw, "StasisTracker");
	callbacks<EventType::OnBuffGainLose>::add_callback(on_buff, "StasisTracker");
}

void Awareness::StasisTracker::on_draw()
{
	for (const auto& hero : stasis_map)
	{
		if (hero.first == local_player && !Menu::spell_tracker_myself->get_bool()) continue;
		if (hero.first != local_player && hero.first->is_ally() && !Menu::spell_tracker_enemies->get_bool()) continue;
		if (!hero.first->is_ally() && !Menu::spell_tracker_enemies->get_bool()) continue;

		float remaining_stasis = hero.second - game_time->get_time();

		if (remaining_stasis < 0.0f) continue;

		char s_remaining_stasis[125];
		sprintf(s_remaining_stasis, "%.2fs", remaining_stasis);

		Vec2 size = draw_manager->calc_text_size(s_remaining_stasis, 40.0f);
		Vec3 world_pos = hero.first->get_position();
		world_pos.x = world_pos.x - (size.x / 2);
		world_pos.z = world_pos.z - 2.0f * size.x;
		Vec2 screen_pos = renderer->world_to_screen(world_pos);
		float fractal = remaining_stasis / 2.5f;

		draw_manager->screen_text(screen_pos, s_remaining_stasis, Color(255, 83, 73), 40.0f);
		draw_manager->arc(local_player->get_position(), 300.0f, -(M_PI / 2), -M_PI * 2.0f * (fractal) - (M_PI / 2), Color(255, 83, 73), 3.0f);
	}
}

void Awareness::StasisTracker::on_buff(Buff* buff, bool gain)
{
	uint32_t hash = buff->get_hash();

	if (gain && (hash == zhonya_buff_hash || hash == bardr_stasis_buff_hash))
	{
		GameObject* owner = buff->get_owner();

		if (auto hero = stasis_map.find(owner); hero != stasis_map.end())
			hero->second = game_time->get_time() + 2.5f;
	}
}