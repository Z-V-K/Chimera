#pragma once
#include "../EvadeSpellData.h"

class Riven
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Riven, "Riven W");
		w_data->set_spell_hashes({ spell_hash("RivenMartyr") })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_fixed(true)
			->set_range(0.f)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_radius(360.f);

		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Riven, "Riven R");
		r_data
			->set_spell_hashes({ spell_hash("RivenIzunaBlade") })
			->set_object_names({ "RivenWindslashMissileCenter", "RivenWindslashMissileLeft", "RivenWindslashMissileRight" })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1600.0f)
			->set_radius(100.0f)
			->set_range(1100.0f)
			->set_multiple_number(3)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_multiple_angle(9.f * M_PI / 180.0f);
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