#pragma once
#include "../EvadeSpellData.h"

class Karthus
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Karthus, "Karthus Q");
		q_data->set_spell_hashes({ spell_hash("KarthusLayWasteA1") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(1.009f)
			->set_missile_speed(FLT_MAX)
			->set_radius(160.0f)
			->set_add_bounding(true)
			->set_range(875.0f);
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