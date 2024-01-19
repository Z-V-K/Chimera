#pragma once

#include "../../../SDK/Geometry.h"

namespace Awareness::WardTracker
{
	namespace Menu
	{
		inline MenuItem* draw_enemy_wards{};
		inline MenuItem* ward_glow_colour{};
		inline MenuItem* ward_range_indicator_col{};
		inline MenuItem* ward_range_indicator_thickness{};
	}

	static void on_draw();
	static void on_draw_environment();
	static void on_slow_tick();
	static void on_create_object(GameObject* obj);
	static void on_delete_object(GameObject* obj);
	inline Geometry::Polygon get_real_ward_range(const Vec3& pos, const int range);
	inline void draw_timer(GameObject* obj);
	inline void draw_minimap_tracker(GameObject* obj);
	inline void glow_ward(GameObject* obj);

	void initialize();
	void on_unload();
};

