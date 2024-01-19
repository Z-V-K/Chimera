#pragma once
#include "../EvadeSpellData.h"

class Zilean
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Zilean, "Zilean Q");
		q_data
			->set_spell_hashes({ spell_hash("ZileanQ") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_add_bounding(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.7f)
			->set_missile_speed(FLT_MAX)
			->set_radius(140.0f)
			->set_range(900.0f);
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