#pragma once
#include "../EvadeSpellData.h"

class Sett
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Sett, "Sett W");
		w_data
			->set_spell_hashes({ spell_hash("SettW") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.75f)
			->set_missile_speed(FLT_MAX)
			->set_radius(30.0f)
			->set_range(800.f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Sett, "Sett E");
		e_data
			->set_spell_hashes({ spell_hash("SettE") })
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_add_bounding(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(140.0f)
			->set_range(500.f)
			->set_offset_start(-500.0f);
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