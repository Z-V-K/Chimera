#pragma once
#include "../EvadeSpellData.h"

class BelVeth
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Belveth, "BelVeth Q");
		//spells.push_back(q_data);
		// TODO;
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Belveth, "BelVeth W");
		w_data->set_spell_hashes({ spell_hash("BelvethW") })
			->set_danger_level(DangerLevel::High)
			->set_is_dangerous(true)
			->set_range(710.f)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_radius(100.f)
			->set_delay(.5f);

		spells.push_back(w_data);
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