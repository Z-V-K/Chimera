#pragma once
#include "../EvadeSpellData.h"

class Poppy
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Poppy, "Poppy Q");
		q_data->set_spell_hashes({ spell_hash("PoppyQ") })
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_delay(1.5f)
			->set_range(450.f)
			->set_radius(80.f)
			->set_offset_start(-50.f)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium);	

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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Poppy, "Poppy R instant");
		r_data->set_spell_hashes({ spell_hash("PoppyRSpellInstant") })
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_delay(.6f)
			->set_radius(90.f)
			->set_range(500.f);

		spells.push_back(r_data);

		r_data = new EvadeSpellData(CharacterHash::Poppy, "Poppy R");
		r_data->set_spell_hashes({ spell_hash("PoppyRSpell") })
			->set_object_names({ "PoppyRMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_delay(.35f)
			->set_missile_speed(2000.f)
			->set_radius(90.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1200.f);

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