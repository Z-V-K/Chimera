#pragma once
#include "../EvadeSpellData.h"

class TwistedFate
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::TwistedFate, "TwistedFate Q");
		q_data
			->set_spell_hashes({ spell_hash("WildCards") })
			->set_object_names({ "SealFateMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1000.0f)
			->set_radius(30.0f)
			->set_range(1450.0f)
			->set_multiple_number(3)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_multiple_angle(28.0f * M_PI / 180.0f);
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