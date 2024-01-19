#pragma once
#include "../EvadeSpellData.h"

class Akshan
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Akshan, "Akshan Q");
		q_data->set_spell_hashes({ spell_hash("AkshanQ") })
			->set_object_names({ "AkshanQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_missile_speed(1500.f)
			->set_range(850.f)
			->set_radius(60.f)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Akshan, "Akshan Q return");
		q_data->set_object_names({ "AkshanQMissileReturn" })
			->set_type(EvadeSpellType::MissileLine)
			->set_delay(0.f)
			->set_missile_speed(2400.f)
			->set_radius(60.f)
			->set_add_bounding(true)
			->set_is_end_pos_to_unit(true)
			->set_is_dangerous(false)
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