#pragma once
#include "../EvadeSpellData.h"

// TODO: Q delay is based on atk_speed
class Senna
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Senna, "Senna Q");
		q_data
			->set_spell_hashes({ spell_hash("SennaQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.4f)
			->set_missile_speed(FLT_MAX)
			->set_radius(50.0f)
			->set_range(1100.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Senna, "Senna W");
		w_data
			->set_spell_hashes({ spell_hash("SennaW") })
			->set_object_names({ "SennaW" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1300.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Senna, "Senna R");
		r_data
			->set_spell_hashes({ spell_hash("SennaR")})
			->set_object_names({ "SennaR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(1.0f)
			->set_missile_speed(20000.0f)
			->set_radius(180.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(20000.0f);
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