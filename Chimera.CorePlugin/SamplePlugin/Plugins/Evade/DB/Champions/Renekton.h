#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Renekton
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
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Renekton, "Renekton E");
		e_data
			->set_spell_hashes({ spell_hash("RenektonDice"), spell_hash("RenektonSliceAndDice") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.0f)
			->set_radius(40.0)
			->set_range(500.0f)
			->set_missile_speed([](DetectedSpell* spell)
			{
				return 760.0f + spell->source->get_movement_speed() ;
			})
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