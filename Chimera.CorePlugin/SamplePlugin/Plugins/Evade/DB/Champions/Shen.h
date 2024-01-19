#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Shen
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Shen, "Shen E");
		e_data
			->set_spell_hashes({ spell_hash("ShenE") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_is_range_limited(true)
			->set_danger_level(DangerLevel::High)
			->set_radius(60.0f)
			->set_range(600.0f)
			->set_extra_range(200.f)
			->set_missile_speed([](DetectedSpell* spell)
			{
				return 800.0f + spell->source->get_movement_speed();
			})
			->set_duration([] (DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell) - .2f;
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