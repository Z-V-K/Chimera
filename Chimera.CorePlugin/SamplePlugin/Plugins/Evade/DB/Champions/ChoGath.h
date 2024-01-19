#pragma once
#include "../EvadeSpellData.h"

class ChoGath
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Chogath, "ChoGath Q");
		q_data->set_spell_hashes({ spell_hash("Rupture") })
			->set_type(EvadeSpellType::Circle)
			->set_range(950.f)
			->set_radius(250.f)
			->set_delay(1.127f)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_dangerous(true);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Chogath, "ChoGath W");
		w_data->set_spell_hashes({ spell_hash("FeralScream") })
			->set_type(EvadeSpellType::Cone)
			->set_range(650.f)
			->set_radius(60.f)
			->set_delay(.5f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true);
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