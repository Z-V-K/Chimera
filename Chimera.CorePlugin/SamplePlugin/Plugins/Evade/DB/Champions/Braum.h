#pragma once
#include "../EvadeSpellData.h"

class Braum
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Braum, "Braum Q");

		q_data->set_spell_hashes({ spell_hash("BraumQ") })
			->set_object_names({ "BraumQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1050.f)
			->set_radius(60.f)
			->set_missile_speed(1700.f)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true);
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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Braum, "Braum R");
		r_data->set_spell_hashes({ spell_hash("BraumRWrapper") })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1250.f)
			->set_radius(115.f)
			->set_delay(.5f)
			->set_missile_speed(1400.f)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_hard_cc(true)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_is_dangerous(true);
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