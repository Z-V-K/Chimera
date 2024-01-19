#pragma once
#include "../EvadeSpellData.h"

class Gangplank
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
		//EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Gangplank, "Gangplank E");
		//spells.push_back(e_data);
		// TODO; trap?
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Gangplank, "Gangplank R");
		r_data->set_spell_hashes({ spell_hash("GangplankR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_duration(8.f)
			->set_radius(525.f)
			->set_range(25000.f);
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