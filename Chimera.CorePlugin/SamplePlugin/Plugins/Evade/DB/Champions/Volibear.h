#pragma once
#include "../EvadeSpellData.h"

class Volibear
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Volibear, "Volibear E");
		e_data
			->set_spell_hashes({ spell_hash("VolibearE") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_duration(2.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(325.0f)
			->set_range(1200.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Volibear, "Volibear R");
		r_data
			->set_spell_hashes({ spell_hash("VolibearR") })
			->set_type(EvadeSpellType::Circle)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_missile_speed(750.0f)
			->set_radius(300.0f)
			->set_range(700.0f)
			->set_delay(1.f);
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