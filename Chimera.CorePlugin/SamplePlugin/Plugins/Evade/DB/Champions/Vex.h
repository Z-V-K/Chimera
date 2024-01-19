#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Vex
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Vex, "Vex Q");
		q_data
			->set_spell_hashes( { spell_hash("VexQ") })
			->set_object_names({ "VexQ" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.15f)
			->set_missile_speed(1200.0f)
			->set_radius(130.0f)
			->set_range(1200.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Vex, "Vex E");
		e_data
			->set_spell_hashes({ spell_hash("VexE") })
			->set_object_names({ "VexE" })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1300.0f)
			->set_range(800.0f)
			->set_radius([](DetectedSpell* spell)
				{
					return std::min(200.0f + 13.0f * (spell->original_start_pos.distance(spell->original_end_pos) / 100.0f), 300.0f);
				});
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Vex, "Vex R");
		r_data
			->set_spell_hashes({ spell_hash("VexR") })
			->set_object_names({ "VexR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1600.0f)
			->set_radius(130.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(2500.0f);
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