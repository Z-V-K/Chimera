#pragma once
#include "../EvadeSpellData.h"

// TODO: Yone W maybe
class Yone
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Yone, "Yone Q");
		q_data
			->set_spell_hashes({ spell_hash("YoneQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.133f)
			->set_missile_speed(1200.0f)
			->set_radius(40.0f)
			->set_range(450.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Yone, "Yone Q3");
		q_data
			->set_spell_hashes({ spell_hash("YoneQ3") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1500.0f)
			->set_radius(80.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1050.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Yone, "Yone R");
		r_data
			->set_spell_hashes({ spell_hash("YoneR") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.75f)
			->set_missile_speed(FLT_MAX)
			->set_radius(112.5f)
			->set_collision_objects({ CollisionObject::Heroes })
			->set_range(1000.0f);
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