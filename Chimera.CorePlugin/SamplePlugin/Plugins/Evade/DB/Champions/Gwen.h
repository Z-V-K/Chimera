#pragma once
#include "../EvadeSpellData.h"

class Gwen
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Gwen, "Gwen Q");
		//spells.push_back(q_data);
		// TODO;
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Gwen, "Gwen R");
		r_data->set_spell_hashes({ spell_hash("GwenR") })
			->set_object_names({ "GwenRMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_missile_speed(1800.f)
			->set_radius(100.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1350.f);
		spells.push_back(r_data);
		//TODO; recast
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