#pragma once
#include "../EvadeSpellData.h"

// TODO: R maybe
class Rumble
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Rumble, "Rumble E");
		e_data
			->set_spell_hashes({ spell_hash("RumbleGrenade") })
			->set_object_names({ "RumbleGrenadeMissile", "RumbleGrenadeMissileDangerZone" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(2000.0f)
			->set_radius(60.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(950.0f);
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