#pragma once
#include "../EvadeSpellData.h"

class TahmKench
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::TahmKench, "TahmKench Q");
		q_data
			->set_spell_hashes({ spell_hash("TahmKenchQ") })
			->set_object_names({ "TahmKenchQ" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(2800.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(900.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::TahmKench, "TahmKench W");
		w_data
			->set_spell_hashes({ spell_hash("TahmKenchW") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_is_hard_cc(true)
			->set_delay(1.5f)
			->set_missile_speed(FLT_MAX)
			->set_radius(275.0f)
			->set_range(1200.0f);
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