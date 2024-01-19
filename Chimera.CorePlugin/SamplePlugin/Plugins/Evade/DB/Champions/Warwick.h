#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Warwick
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
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Warwick, "Warwick R");
		r_data
			->set_spell_hashes({ spell_hash("WarwickR") })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.1f)
			->set_radius(150.0f)
			->set_collision_objects({ CollisionObject::Heroes })
			->set_range([](DetectedSpell* spell)
				{
					return spell->source? spell->source->get_movement_speed() * 2.5f : 1450.0f;
				})
			->set_missile_speed([](DetectedSpell* spell)
				{
					return spell->source ? spell->source->get_movement_speed() * 4.9f : 2200.0f;
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