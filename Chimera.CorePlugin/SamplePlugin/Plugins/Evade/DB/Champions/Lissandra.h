#pragma once
#include "../EvadeSpellData.h"

class Lissandra
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Lissandra, "Lissandra Q");
		q_data->set_spell_hashes({ spell_hash("LissandraQ") })
			->set_object_names({ "LissandraQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(2200.0f)
			->set_radius(75.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(825.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Lissandra, "Lissandra Q Shards");
		q_data->set_object_names({ "LissandraQShards" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.0f)
			->set_missile_speed(2200.0f)
			->set_radius(90.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(100.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		// TODO;
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Lissandra, "Lissandra E");
		e_data->set_spell_hashes({ spell_hash("LissandraEMissile") })
			->set_object_names({ "LissandraEMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(125.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1025.0f);
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