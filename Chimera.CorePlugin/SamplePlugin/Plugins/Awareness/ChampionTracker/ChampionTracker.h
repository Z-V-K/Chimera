#pragma once

namespace Awareness::ChampionTracker
{
	namespace Menu
	{
		inline MenuTab* distance_tracker{};
		inline MenuTab* fow_tracker{};
		inline MenuItem* show_distance_tracker{};
		inline MenuItem* show_fow_tracker{};
		inline MenuItem* draw_estimated_zone_on_minimap{};
		inline MenuItem* show_champion_outline{};
		inline MenuItem* show_champion_outline_color{};
	}

	struct ChampionsToBeTracked
	{
		ChampionsToBeTracked(GameObject* entity)
		{
			hero = entity;
		}

		GameObject* hero;
		Vec3 last_position = { 0,0,0 };
		float last_seen;
		Vec2 distance = { 0,0 }; // distance, r
		Vec2 minimap_position = { 0,0 };
		bool is_missing = false;
	};

	static void on_draw_environment();
	static void on_slow_tick();
	static void on_draw();
	void initialize();
};