#pragma once
#include "../EvadeSpellData.h"

class JarvanIV
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::JarvanIV, "JarvanIV Q");
		q_data->set_spell_hashes({ spell_hash("JarvanIVDragonStrike") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(.4f)
			->set_radius(68.f)
			->set_range(785.f);
		spells.push_back(q_data);

		// TODO; extended/standard Q
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::JarvanIV, "JarvanIV E");
		e_data->set_spell_hashes({ spell_hash("JarvanIVDemacianStandard") })
			->set_type(EvadeSpellType::Circle)
			->set_danger_level(DangerLevel::Low)
			->set_is_range_limited(true)
			->set_delay(0.f)
			->set_missile_speed(1450.f)
			->set_radius(200.f)
			->set_range(860.f);
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