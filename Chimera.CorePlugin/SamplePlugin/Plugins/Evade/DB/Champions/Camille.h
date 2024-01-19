#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Camille
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Camille, "Camille W");
		w_data->set_spell_hashes({ spell_hash("CamilleW") })
			->set_type(EvadeSpellType::Cone)
			->set_range(640.f)
			->set_radius(70.f)
			->set_delay(1.f)
			->set_danger_level(DangerLevel::Medium)
			->set_is_start_pos_from_unit(true)
			->set_is_dangerous(true);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Camille, "Camille E");
		e_data->set_spell_hashes({ spell_hash("CamilleEDash2") })
			->set_type(EvadeSpellType::MissileLine)
			->set_radius(130.f)
			->set_delay(0.f)
			->set_missile_speed(1050.f)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_is_hard_cc(true)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dash(true)
			->set_collision_objects({ CollisionObject::Heroes })
			->set_missile_speed([](DetectedSpell* spell)
			{
				return 1050.f + (spell->source != nullptr ? spell->source->get_movement_speed() : 0.f);
			})
			->set_duration([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			})
			->set_range([](DetectedSpell* spell)
			{
				if (!spell->source)
					return 1000.f + local_player->get_bounding_radius();

				if (spell->source->get_distance(local_player) <= 1200.f)
					return 1000.f + local_player->get_bounding_radius();

				return 600.f + local_player->get_bounding_radius();
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
