#pragma once
#include "../EvadeSpellData.h"

class Alistar
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Alistar, "Alistar Q");
		q_data->set_spell_hashes({ spell_hash("Pulverize") })
			->set_type(EvadeSpellType::Circle)
			->set_range(375.f)
			->set_radius(375.f)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High);
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