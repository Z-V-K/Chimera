#pragma once
#include "../EvadeSpellData.h"

class Malzahar
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Malzahar, "Malzahar Q");
		q_data->set_spell_hashes({ spell_hash("MalzaharQ") })
			//->set_object_names({ "MalzaharQMissile" })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.85f)
			->set_missile_speed(FLT_MAX)
			->set_radius(85.0f)
			->set_range(750.0f)
			->set_is_perpendicular(true)
			->set_perpendicular_length(450.f);
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