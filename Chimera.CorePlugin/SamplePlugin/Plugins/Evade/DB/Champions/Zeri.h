#pragma once
#include "../EvadeSpellData.h"

// TODO: W wall range extension
class Zeri
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Zeri, "Zeri W");
		w_data
			->set_spell_hashes({ spell_hash("ZeriW") })
			->set_object_names({ "ZeriW" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.5f)
			->set_missile_speed(2500.0f)
			->set_radius(40.0f)
			->set_range(1200.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Zeri, "Zeri R");
		r_data
			->set_spell_hashes({ spell_hash("ZeriR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(825.0f)
			->set_range(825.0f);
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