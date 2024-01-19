#pragma once
#include "../EvadeSpellData.h"

class Sivir
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Sivir, "Sivir Q");
		q_data
			->set_spell_hashes({ spell_hash("SivirQ") })
			->set_object_names({ "SivirQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1450.0f)
			->set_radius(90.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1250.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Sivir, "Sivir Q Return");
		q_data
			->set_spell_hashes({ spell_hash("SivirQReturnWaybackMissileOnly") })
			->set_object_names({ "SivirQMissileReturn" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_end_pos_to_unit(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.0f)
			->set_missile_speed(1200.0f)
			->set_radius(100.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(20000.0f);
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