#pragma once
#include "../EvadeSpellData.h"

class Annie
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Annie, "Annie W");

		w_data->set_spell_hashes({ spell_hash("AnnieW") })
			->set_type(EvadeSpellType::Cone)
			->set_range(625.f)
			->set_radius(60.f)
			->set_danger_level(DangerLevel::Medium);

		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Annie, "Annie R");
		r_data->set_spell_hashes({ spell_hash("AnnieR") })
			->set_type(EvadeSpellType::Circle)
			->set_range(600.f)
			->set_radius(250.f)
			->set_danger_level(DangerLevel::Extreme)
			->set_is_dangerous(true)
			->set_is_hard_cc(true);

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