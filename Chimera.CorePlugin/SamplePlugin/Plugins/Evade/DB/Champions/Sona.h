#pragma once
#include "../EvadeSpellData.h"

class Sona
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
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Sona, "Sona R");
		r_data
			->set_spell_hashes({ spell_hash("SonaR") })
			->set_object_names({ "SonaR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_hard_cc(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_delay(0.25f)
			->set_missile_speed(2400.0f)
			->set_radius(140.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1000.0f);
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