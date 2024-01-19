#include "ChampionTracker.h"
#include "../Awareness.h"
#include "../Colors.h"

float ct_font_size = 10.0f;
float r = 300.0f; // orbit radius
Vec2 textureSize = { 25.0f, 50.0f }; // min, max
Vec2 minimapTextureSize = { 25.0f, 25.0f }; // width, height
std::vector<Awareness::ChampionTracker::ChampionsToBeTracked> championData;

void Awareness::ChampionTracker::initialize()
{
	Color white = { 255, 255, 255, 255 };
	Menu::distance_tracker = Awareness::Menu::tab_champion_tracker->add_menu("mgChampionDistanceTracker", "Distance Tracker", ICON_FA_ARROWS_ALT_H);
	Menu::fow_tracker = Awareness::Menu::tab_champion_tracker->add_menu("fow_tracker", "FOW Tracker", ICON_FA_LOW_VISION);
	Menu::show_distance_tracker = Menu::distance_tracker->add_checkbox("show_distance_tracker", "Show Distance Tracker", true);
	Menu::show_fow_tracker = Menu::fow_tracker->add_checkbox("show_fow_tracker", "Show FOW Tracker", true);
	Menu::draw_estimated_zone_on_minimap = Menu::fow_tracker->add_checkbox("memeDrawEstimatedZoneOnMinimap", "Draw Esitmated Progression on Minimap", true);
	Menu::show_champion_outline = Menu::fow_tracker->add_checkbox("show_champion_outline", "Draw Champion Outline", true);
	Menu::show_champion_outline_color = Menu::fow_tracker->add_colorpick("show_champion_outline_color", "^- Color", white);

	Menu::distance_tracker->set_enabled(Menu::show_distance_tracker);
	Menu::fow_tracker->set_enabled(Menu::show_fow_tracker);

	callbacks<EventType::OnDrawEnvironment>::add_callback(on_draw_environment, "ChampionTracker");
	callbacks<EventType::OnDraw>::add_callback(on_draw, "ChampionTracker");
	callbacks<EventType::OnSlowTick>::add_callback(on_slow_tick, "ChampionTracker");

	for (const auto& champion : entities->get_heroes())
	{
		if (champion->is_enemy())
			championData.push_back(ChampionsToBeTracked(champion));
	}
}
void Awareness::ChampionTracker::on_draw_environment()
{
	if (!Menu::show_distance_tracker->get_bool())
		return;

	for (const auto& enemy : entities->get_heroes())
	{
		if (!enemy || !enemy->is_enemy() || !enemy->is_alive() || !enemy->is_visible() || enemy->is_visible_on_screen()) 
			continue;

		Vec2 hpIndicatorRoot{};
		Vec2 currTextureSize{};
		Vec2 root{ renderer->world_to_screen(local_player->get_position()) };
		Vec2 circlePoint{};
		Vec3 distance{};
		float theta{};
		float fractal{};

		distance.x = enemy->get_position().x - local_player->get_position().x;
		distance.y = enemy->get_position().z - local_player->get_position().z;
		distance.z = sqrtf(powf(distance.x, 2) + powf(distance.y, 2));

		theta = atan2(distance.y, distance.x);

		circlePoint.x = root.x + r * cos(theta) - (textureSize.x / 2);
		circlePoint.y = root.y - r * sin(theta) - (textureSize.y / 2);

		if (distance.z < 1000.0f)
		{
			currTextureSize.x = textureSize.x;
			currTextureSize.y = textureSize.x;
		}
		else if (distance.z > 3000.0f)
		{
			continue;
		}
		else
		{
			float fractal{ distance.z / 3000.0f };
			currTextureSize.x = fractal * textureSize.y;
			currTextureSize.y = fractal * textureSize.y;
		}

		hpIndicatorRoot.x = circlePoint.x + currTextureSize.x / 2;
		hpIndicatorRoot.y = circlePoint.y + currTextureSize.x / 2;

		fractal = enemy->get_health() / enemy->get_max_health();

		draw_manager->texture(enemy->get_circle_icon(), circlePoint, currTextureSize, 0.0f, Color{ 255, 255, 255, 255 });
		draw_manager->screen_arc(hpIndicatorRoot, currTextureSize.x / 2, -(M_PI / 2), -M_PI * 2.0f * (fractal)-(M_PI / 2), Colors::SpellTracker::dark_red, 3.0f);
	}
}

void Awareness::ChampionTracker::on_draw()
{
	for (const auto& enemy : championData)
	{
		if (!enemy.is_missing || enemy.last_position == Vec3{ 0,0,0 }) continue;

		float delta = game_time->get_time() - enemy.last_seen;

		if (delta > 0.0 && delta < 30.0f)
		{
			std::string time_missing = std::to_string(static_cast<int>(delta));
			Vec2 text_size = draw_manager->calc_text_size(time_missing, ct_font_size);
			Vec2 minimap_pos = renderer->world_to_minimap(enemy.last_position) - (text_size / 2);

			draw_manager->texture(enemy.hero->get_circle_icon(), enemy.minimap_position - (minimapTextureSize.x / 2), minimapTextureSize, 0.0f, Color{ 100, 100, 100, 255 });
			draw_manager->screen_text(minimap_pos, time_missing, Color{ 255, 255, 255, 255 }, ct_font_size);
			draw_manager->screen_circle_minimap(renderer->world_to_minimap(enemy.last_position), enemy.distance.y, Colors::ChampionTracker::red, 2.0f);
		}
	}
}

void Awareness::ChampionTracker::on_slow_tick()
{
	for (auto& enemy : championData)
	{
		if (!enemy.hero) 
			continue;

		if (!enemy.hero->is_visible())
		{
			enemy.is_missing = true;


		}
		else
		{
			enemy.last_seen = game_time->get_time();
			enemy.is_missing = false;
			enemy.last_position = enemy.hero->get_position();

			enemy.minimap_position = renderer->world_to_minimap(enemy.last_position);

			if (enemy.distance.y != 0) enemy.distance.y = 0;
		}

		if (enemy.hero->is_alive() && !enemy.hero->is_visible())
		{
			auto dx = enemy.last_position.x - local_player->get_position().x;
			auto dy = enemy.last_position.y - local_player->get_position().y;
			enemy.distance.x = sqrtf(powf(dx, 2) + powf(dy, 2)); 

			enemy.distance.y += (enemy.hero->get_movement_speed() / 30) * (minimap->get_size().x / 14800.f);
		}
	}
}