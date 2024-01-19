#pragma once
#include "../EvadeSpellData.h"

class Elise
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Elise, "Elise E");
		e_data->set_spell_hashes({ spell_hash("EliseHumanE") })
			->set_object_names({ "EliseHumanE" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_hard_cc(true)
			->set_missile_speed(1600.f)
			->set_radius(55.f)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Minions, CollisionObject::Heroes })
			->set_range(1100.f);
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