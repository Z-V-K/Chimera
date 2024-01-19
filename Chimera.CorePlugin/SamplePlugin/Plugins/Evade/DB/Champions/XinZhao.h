#pragma once
#include "../EvadeSpellData.h"

class XinZhao
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::XinZhao, "XinZhao W");
		w_data
			->set_spell_hashes({ spell_hash("XinZhaoW") })
			->set_object_names({ "XinZhaoWMissile" })
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_add_bounding(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.5f)
			->set_missile_speed(6250.0f)
			->set_radius(40.0f)
			->set_range(1000.0f);
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