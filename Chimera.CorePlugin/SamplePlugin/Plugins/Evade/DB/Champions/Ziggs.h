#pragma once
#include "../EvadeSpellData.h"

// TODO: Q bounce
// TODO: E small balls through particles
class Ziggs
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Ziggs, "Ziggs Q");
		q_data
			->set_spell_hashes({ spell_hash("ZiggsQ") })
			->set_object_names({ "ZiggsQSpell" })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_limited(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1700.0f)
			->set_radius(150.0f)
			->set_range(850.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Ziggs, "Ziggs W");
		w_data
			->set_spell_hashes({ spell_hash("ZiggsW") })
			->set_object_names({ "ZiggsW" })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.7f)
			->set_missile_speed(1750.0f)
			->set_radius(325.0f)
			->set_range(1000.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Ziggs, "Ziggs R");
		r_data
			->set_spell_hashes({ spell_hash("ZiggsR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.375f)
			->set_duration(1.3f)
			->set_missile_speed(FLT_MAX)
			->set_radius(505.0f)
			->set_range(5000.0f);
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