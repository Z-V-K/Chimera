#pragma once
#include "../Awareness.h"
#include "../Colors.h"

namespace Awareness::Hud
{
	namespace Menu
	{
		inline MenuItem* show_hud{};
		inline MenuItem* hud_position_horizontal{};
		inline MenuItem* hud_position_vertical{};
	}

	void initialize();
	void init_menu();
	void on_slow_tick();
	void on_draw();
	int get_xp_lower_bound(int level);
	int get_xp_higher_bound(int level);
	void draw_base(const Vec2& offset, GameObject* enemy);
	void draw_spells(const Vec2& offset, GameObject* enemy, const SlotId spell_slot_id);
	void draw_hp(const Vec2& offset, GameObject* enemy);
	void draw_mana(const Vec2& offset, GameObject* enemy);
	void draw_xp_arc(const Vec2& offset, GameObject* enemy);
};