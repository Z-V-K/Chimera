#pragma once
#include "../EvadeSpellData.h"

// TODO: Q Cone?
class Swain
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Swain, "Swain W");
		w_data
			->set_spell_hashes({ spell_hash("SwainW") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(1.5f)
			->set_missile_speed(FLT_MAX)
			->set_radius(325.0f)
			->set_range(7500.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Swain, "Swain E");
		e_data
			->set_spell_hashes({ spell_hash("SwainE") })
			->set_object_names({ "SwainE" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(935.0f)
			->set_radius(85.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1025.0f); // wiki 850.0f 
		spells.push_back(e_data);

		e_data = new EvadeSpellData(CharacterHash::Swain, "Swain E Return");
		e_data
			->set_object_names({ "SwainEReturnMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_end_pos_to_unit(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_missile_speed(600.0f)
			->set_radius(85.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(20000.0f);
		spells.push_back(e_data);
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