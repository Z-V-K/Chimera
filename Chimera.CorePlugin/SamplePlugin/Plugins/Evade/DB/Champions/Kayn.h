#pragma once
#include "../EvadeSpellData.h"

class Kayn
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Kayn, "Kayn Q");
		q_data->set_spell_hashes({ spell_hash("KaynQ") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_is_range_fixed(true)
			->set_delay(0.5f)
			->set_range(350.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(350.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Kayn, "Kayn W");
		w_data->set_spell_hashes({ spell_hash("KaynW") })
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.55f)
			->set_missile_speed(FLT_MAX)
			->set_radius(110.0f) // 90 original
			->set_range(750.0f);
		spells.push_back(w_data);

		w_data = new EvadeSpellData(CharacterHash::Kayn, "Kayn Blue W");
		w_data->set_spell_hashes({ spell_hash("KaynAssW") })
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.60f)
			->set_missile_speed(FLT_MAX)
			->set_radius(110.0f) // 90 original
			->set_range(950.0f);
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