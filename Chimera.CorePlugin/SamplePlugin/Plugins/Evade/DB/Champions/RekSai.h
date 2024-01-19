#pragma once
#include "../EvadeSpellData.h"

class RekSai
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::RekSai, "RekSai Q Burrowed");
		q_data
			->set_spell_hashes({ spell_hash("RekSaiQBurrowed") })
			->set_object_names({ "RekSaiQBurrowedMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.1f)
			->set_missile_speed(1950.0f)
			->set_radius(60.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1500.0f);
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