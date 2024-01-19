#pragma once
#include "../EvadeSpellData.h"

class Tryndamere
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Tryndamere, "Tryndamere E");
		e_data
			->set_spell_hashes({ spell_hash("slash") })
			->set_type(EvadeSpellType::MissileLine)
			->set_danger_level(DangerLevel::Low)
			->set_delay(0.0f)
			->set_missile_speed(1000.0f)
			->set_radius(225.0f)
			->set_range(660.f)
			->set_extra_range(200.0f)
			->set_duration([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			});
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