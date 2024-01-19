#pragma once

namespace Awareness::SpellTracker
{
	struct CastedSpell
	{
		SpellSlot* spell;
		float last_cast;
		float ammo_recharge;
		float ability_haste;

		float get_cooldown() const
		{
			if (last_cast == 0.f)
				return 0.f;

			const auto max_cd = (spell->get_slot_id() == SlotId::Summoner1 || spell->get_slot_id() == SlotId::Summoner2) ? 
									get_max_cooldown() : get_cooldown_mod() * get_max_cooldown();
			const auto gametime = game_time->get_time();
			return last_cast + max_cd - gametime;
		}

		void update(float haste)
		{
			last_cast = game_time->get_time();
			ability_haste = haste;
		}

		float get_max_cooldown() const
		{
			if (spell->get_ammo() > 0) {
				return spell->get_spell_data()->cooldown_time()[spell->get_level()];
			}
			if (spell->get_ammo_cooldown() != 0.f) {
				return spell->get_spell_data()->mAmmoRechargeTime()[spell->get_level()] - spell->get_spell_data()->cooldown_time()[spell->get_level()];

			}

			return spell->get_spell_data()->cooldown_time()[spell->get_level()];
		}

		bool is_ready() const
		{
			return get_cooldown() <= 0;
		}

		float get_cooldown_mod() const
		{
			return 100.0f / (100.0f + ability_haste);
		}
	};

	namespace Menu
	{
		inline MenuTab*  spell_tracker{};
		inline MenuTab*	 spell_tracker_design{};
		inline MenuItem* spell_tracker_design_choice{};
		inline MenuItem* spell_tracker_me{};
		inline MenuItem* spell_tracker_enemies{};
		inline MenuItem* spell_tracker_allies{};
	}

	void draw_xp_bar(GameObject* entity);

	namespace LegacyTracker
	{
		inline void draw_spell_tracker(GameObject* entity, const std::vector<SpellSlot*>& slots);
		inline void draw_level_indicator(const Vec2& root, SpellSlot* spell);
		inline void draw_progress_bar(const CastedSpell& spell, const Vec2& root, bool is_stasis = false);
	}

	namespace ModernTracker
	{
		inline void draw_spell_tracker(GameObject* entity, const std::vector<SpellSlot*>& slots);
		inline void draw_progress_bar(const CastedSpell& spell, const Vec2& root, bool is_stasis = false);
	}

	namespace ChimeraTracker
	{
		inline void draw_spell_tracker(GameObject* entity, const std::vector<SpellSlot*>& slots);
		inline void draw_level_indicator(const Vec2& root, SpellSlot* spell, bool is_stasis);
		inline void draw_progress_bar(const CastedSpell& spell, const Vec2& root, bool is_stasis = false);
	}

	static void on_process_spell_cast(SpellCastInfo* spell);
	static void on_draw();

	void initialize();
	void draw_trackers(GameObject* entity);
};