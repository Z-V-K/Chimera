#pragma once
#include "../EvadeSpellData.h"

class Xerath
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Xerath, "Xerath Q");
		q_data
			->set_spell_hashes({ spell_hash("XerathArcanopulse2") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.528f)
			->set_missile_speed(FLT_MAX)
			->set_radius(70.0f)
			->set_range(1450.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Xerath, "Xerath W");
		w_data
			->set_spell_hashes({ spell_hash("XerathArcaneBarrage2") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.778f)
			->set_missile_speed(FLT_MAX)
			->set_radius(275.0f)
			->set_range(1000.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Xerath, "Xerath E");
		e_data
			->set_spell_hashes({ spell_hash("XerathMageSpear") })
			->set_object_names({ "XerathMageSpearMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_is_start_pos_updated_on_flash(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1400.0f)
			->set_radius(60.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1130.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Xerath, "Xerath R");
		r_data
			->set_spell_hashes({ spell_hash("XerathRMissileWrapper") })
			->set_object_names({ "XerathLocusPulse" })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.627f)
			->set_missile_speed(FLT_MAX)
			->set_radius(200.0f)
			->set_range(5000.0f);
		spells.push_back(r_data);
	}
public:
	static void load(std::vector<EvadeSpellData*>& spells)
	{
		load_q_data(spells);
		load_w_data(spells);
		load_e_data(spells);
		load_r_data(spells);
	}
};