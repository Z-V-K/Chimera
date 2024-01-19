#pragma once
#include "../EvadeSpellData.h"

class Darius
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Darius, "Darius Q");
		q_data->set_spell_hashes({ spell_hash("DariusCleave") })
			->set_type(EvadeSpellType::Ring)
			->set_radius(230.f)
			->set_ring_radius(150.f)
			->set_delay(1.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_end_pos_to_unit(true)
			->set_is_start_pos_from_unit(true)
			->set_add_bounding(true)
			->set_is_dangerous(true);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Darius, "Darius E");
		e_data->set_spell_hashes({ spell_hash("DariusAxeGrabCone") })
			->set_type(EvadeSpellType::Cone)
			->set_range(575.f)
			->set_radius(65.f)
			->set_danger_level(DangerLevel::High)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true);
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