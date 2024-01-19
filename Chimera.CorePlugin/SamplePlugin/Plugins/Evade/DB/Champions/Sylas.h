#pragma once
#include "../EvadeSpellData.h"

class Sylas
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Sylas, "Sylas Q");
		q_data
			->set_spell_hashes({ spell_hash("SylasQ") })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_limited(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.4f + 0.6f) // + 0.6f detonation
			->set_missile_speed(FLT_MAX)
			->set_radius(180.0f)
			->set_range(775.0f - 180.0f / 4); // idk wtf hes doing here looks retarded
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Sylas, "Sylas E");
		e_data
			->set_spell_hashes({ spell_hash("SylasE2") })
			->set_object_names({ "SylasE2" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1600.0f)
			->set_radius(60.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(850.0f);
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