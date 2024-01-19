#pragma once
#include "../EvadeSpellData.h"

class Nilah
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Nilah, "Nilah Q");
		q_data
			->set_spell_hashes({ spell_hash("NilahQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(75.0f)
			->set_range(600.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Nilah, "Nilah E");
		e_data
			//->spellNames({ "NilahEQ" })
			->set_object_names({ "NilahEQMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.25f)
			->set_missile_speed(1000.0f)
			->set_radius(75.0f)
			->set_range(800.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Nilah, "Nilah R");
		r_data
			->set_spell_hashes({ spell_hash("NilahR") })
			->set_type(EvadeSpellType::Circle)
			->set_add_bounding(false)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_is_end_pos_to_unit(true)
			->set_delay(1.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(450.0f)
			->set_range(450.0f);
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