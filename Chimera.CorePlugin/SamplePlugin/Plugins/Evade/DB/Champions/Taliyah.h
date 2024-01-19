#pragma once
#include "../EvadeSpellData.h"

// TODO: R maybe
class Taliyah
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Taliyah, "Taliyah Q");
		q_data
			->set_spell_hashes({ spell_hash("TaliyahQ") })
			->set_object_names({ "TaliyahQMis", "TaliyahQMisBig" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.0f) // 0.25 first one
			->set_missile_speed(3600.0f)
			->set_radius(100.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1000.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Taliyah, "Taliyah W");
		w_data
			->set_spell_hashes({ spell_hash("TaliyahWVC") })
			->set_type(EvadeSpellType::Circle)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.792f)
			->set_missile_speed(FLT_MAX)
			->set_radius(225.0f)
			->set_range(900.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
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