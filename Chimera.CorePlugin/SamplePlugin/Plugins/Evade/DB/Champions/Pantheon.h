#pragma once
#include "../EvadeSpellData.h"

class Pantheon
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Pantheon, "Pantheon Q Melee");
		q_data
			->set_spell_hashes({ spell_hash("PantheonQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Low)
			->set_delay(.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(80.0f)
			->set_range(670.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Pantheon, "Pantheon Q Range");
		q_data
			->set_spell_hashes({ spell_hash("PantheonQMissile") })
			->set_object_names({ "PantheonQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(2700.0f)
			->set_radius(55.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1200.0f);
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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Pantheon, "Pantheon R");
		r_data
			->set_spell_hashes({ spell_hash("PantheonR") })
			->set_type(EvadeSpellType::Circle)
			->set_add_bounding(true)
			->set_is_range_limited(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(4.2f)
			->set_missile_speed(2700.0f)
			->set_radius(450.0f)
			->set_range(5500.0f);
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