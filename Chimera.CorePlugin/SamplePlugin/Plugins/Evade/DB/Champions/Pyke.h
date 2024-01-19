#pragma once
#include "../EvadeSpellData.h"

// TODO: R
class Pyke
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Pyke, "Pyke Q Stab");
		q_data
			->set_spell_hashes({ spell_hash("PykeQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(70.0f)
			->set_range(400.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Pyke, "Pyke Q Hook");
		q_data
			->set_spell_hashes({ spell_hash("PykeQRange") })
			->set_object_names({ "PykeQRange" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(2000.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1100.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Pyke, "Pyke E");
		e_data
			->set_spell_hashes({ spell_hash("PykeE") })
			->set_object_names({ "PykeEMissile" })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_follow_cast_direction(true)
			->set_is_end_pos_to_unit(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(1.0f)
			->set_missile_speed(3000.0f)
			->set_radius(110.0f)
			->set_range(550.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Pyke, "Pyke R");
		//spells.push_back(r_data);
		// TODO;
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