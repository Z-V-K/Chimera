#pragma once

namespace Orbwalker
{
	namespace Menu 
	{
		inline MenuTab* main_menu{};
		
		inline MenuTab* visuals{};
		inline MenuItem* glow_player{};
		inline MenuItem* glow_player_color{};

		inline MenuItem* debug{};

		inline MenuTab* hotkeys{};
		inline MenuItem* hotkey_combo{};
		inline MenuItem* hotkey_lane_clear{};
		inline MenuItem* hotkey_fast_lane_clear{};
		inline MenuItem* hotkey_harass{};
		inline MenuItem* hotkey_last_hit{};
		inline MenuItem* hotkey_flee{};
		inline MenuItem* hotkey_none{};

		inline MenuItem* lasthit_barrels{};
		inline MenuItem* lasthit_jungle{};

		inline MenuItem* harass_under_turret{};
		inline MenuItem* harass_focus_mode{};

		inline MenuTab* settings{}; 
		inline MenuItem* combo_without_move{};
		inline MenuItem* limit_attack{};
		inline MenuItem* hold_radius{};

		inline MenuTab* delays{};
		inline MenuItem* windup_delay{};

		inline MenuTab* advanced{};
		inline MenuItem* missile_check{};
		//inline MenuItem* yasuo_wall_check{};
	}

	bool combo_mode();
	bool last_hit_mode();
	bool lane_clear_mode();
	bool harass_mode();
	bool flee_mode();

	OrbwalkerMode orbwalker_mode();

	void on_process_spell(SpellCastInfo* processed_spell);
	void on_cast_complete(SpellCastInfo* processed_spell);
	void on_stop_cast(SpellCastInfo* spell, bool destroy_missile, bool animation_cancelled);
	void on_issue_order(IssueOrderType order, Vec3* position, GameObject* target, bool* process);
	void on_game_update();
	void on_draw();

	void on_cast_complete_delayed(SpellCastInfo* processed_spell);

	bool can_move();
	bool can_move(float extra_windup);
	bool can_attack();
	bool can_attack(float extra_windup);
	bool can_attack_with_windwall(GameObject* target);

	float get_attack_cast_delay();

	void orbwalk(GameObject* target, const Vec3& pos);
	bool attack(GameObject* target);
	void move(const Vec3& pos);

	bool can_last_hit(GameObject* minion, int delay);
	bool should_prepare_for_turret(GameObject* minion);
	int time_for_auto_to_reach_target(GameObject* source, GameObject* target);

	void reset_auto_attack_timer(int delay = 0);

	bool is_priority_minion(GameObject* minion);
	GameObject* should_wait_laneclear(const std::vector<GameObject*>& minions);
	GameObject* should_wait_lasthit(const std::vector<GameObject*>& minions);

	GameObject* get_target();
	GameObject* get_target_combo();
	GameObject* get_target_harass();
	GameObject* get_target_laneclear();
	GameObject* get_target_lasthit();

	OrbwalkerMode get_mode();

	void make_player_glow();

	void initialize();
	void on_unload();
};