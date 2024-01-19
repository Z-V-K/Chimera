#pragma once
#include "../EvadeSpellData.h"

class Malphite
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
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Malphite, "Malphite R");
		r_data->set_spell_hashes({ spell_hash("UFSlash") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_is_range_limited(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_missile_speed(1500.0f) // 1500 + 100% ms
			->set_radius(325.0f)
			->set_range(1000.0f)
			->set_is_hard_cc(true)
			->set_missile_speed([](DetectedSpell* spell)
			{
				return spell->source ? 1500.f + spell->source->get_movement_speed() : 1500.f;
			})
			->set_delay([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			});
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