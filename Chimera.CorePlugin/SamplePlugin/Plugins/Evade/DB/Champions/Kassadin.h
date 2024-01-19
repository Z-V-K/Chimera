#pragma once
#include "../EvadeSpellData.h"

class Kassadin
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Kassadin, "Kassadin E");
		e_data->set_spell_hashes({ spell_hash("ForcePulse") })
			->set_type(EvadeSpellType::Cone)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_duration(0.5f)
			->set_missile_speed(FLT_MAX)
			->set_radius(78.0f)
			->set_range(600.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Kassadin, "Kassadin R");
		r_data->set_spell_hashes({ spell_hash("RiftWalk") })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_limited(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(250.0f)
			->set_range(500.0f);
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