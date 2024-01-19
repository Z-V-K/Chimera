#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Tristana
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Tristana, "Tristana W");
		w_data
			->set_spell_hashes({ spell_hash("TristanaW") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_is_range_limited(true)
			->set_danger_level(DangerLevel::Medium)
			->set_radius(350.0f)
			->set_range(900.0f)
			->set_missile_speed(1100.f)
			->set_delay([](DetectedSpell* spell)
			{
				return .25f + spell->get_range() / spell->spell_data->missile_speed(spell);
			});
			//->set_missile_speed([](DetectedSpell* spell) 
			//	{ 
			//		return std::min(150.0f + (spell->original_start_pos.distance(spell->get_end_pos()) * 1.05f), 1100.0f); 
			//	});
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