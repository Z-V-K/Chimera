#pragma once
#include "../EvadeSpellData.h"

class Katarina
{
private:
	// TODO; ground daggers
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Katarina, "Katarina R");
		r_data->set_spell_hashes({ spell_hash("KatarinaR") })
			->set_type(EvadeSpellType::Circle)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_duration(.5f)
			->set_missile_speed(2400.0f)
			->set_radius(550.0f)
			->set_range(625.0f);
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