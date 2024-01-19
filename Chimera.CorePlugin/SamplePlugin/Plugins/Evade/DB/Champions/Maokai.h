#pragma once
#include "../EvadeSpellData.h"

class Maokai
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Maokai, "Maokai Q");
		q_data->set_spell_hashes({ spell_hash("MaokaiQ") })
			->set_object_names({ "MaokaiQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.3889f)
			->set_missile_speed(1600.0f)
			->set_radius(55.0f)
			->set_range(650.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Maokai, "Maokai E");
		//spells.push_back(e_data);
		// TODO;
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Maokai, "Maokai R");
		//spells.push_back(r_data);
		// TODO;
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