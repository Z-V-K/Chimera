#pragma once
#include "../EvadeSpellData.h"

class Kled
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Kled, "Kled Q Skaarl");
		q_data->set_spell_hashes({ spell_hash("KledQ") })
			->set_object_names({ "KledQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(40.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(800.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Kled, "Kled Q");
		q_data->set_spell_hashes({ spell_hash("KledRiderQ") })
			->set_object_names({ "KledRiderQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(3000.0f)
			->set_radius(40.0f)
			->set_range(750.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_multiple_number(5)
			->set_multiple_angle(5.0f * M_PI / 180.0f);

		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		// TODO;
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