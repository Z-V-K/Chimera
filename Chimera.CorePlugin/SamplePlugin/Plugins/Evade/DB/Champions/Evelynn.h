#pragma once
#include "../EvadeSpellData.h"

class Evelynn
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Evelynn, "Evelynn Q");
		q_data->set_spell_hashes({ spell_hash("EvelynnQ") })
			->set_object_names({ "EvelynnQ" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true)
			->set_delay(.3f)
			->set_missile_max_speed(2400.f)
			->set_radius(60.f)
			->set_collision_objects({ CollisionObject::Minions, CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(900.f);
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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Evelynn, "Evelynn R");
		r_data->set_spell_hashes({ spell_hash("EvelynnR") })
			->set_type(EvadeSpellType::Cone)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_delay(.35f)
			->set_radius(250.f)
			->set_range(500.f);
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