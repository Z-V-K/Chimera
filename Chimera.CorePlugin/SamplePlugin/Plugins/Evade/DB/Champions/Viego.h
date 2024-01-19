#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Viego
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Viego, "Viego Q");
		q_data
			->set_spell_hashes({ spell_hash("ViegoQ") })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.35f)
			->set_offset_start(-25.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(62.5f)
			->set_range(600.0f + 25.0f)
			->set_delay([](DetectedSpell* spell)
				{
					return spell->source->get_attack_cast_delay() * 1.4f;
				});
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Viego, "Viego W");
		w_data
			//->spellNames({ "ViegoW" })
			->set_object_names({ "ViegoWMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			//->isRangeFixed(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_missile_speed(1300.0f)
			->set_radius(60.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(900.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Viego, "Viego R");
		r_data
			->set_spell_hashes({ spell_hash("ViegoR") })
			->set_type(EvadeSpellType::Circle)
			->set_is_range_limited(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.5f)
			->set_missile_speed(2500.0f)
			->set_radius(300.0f)
			->set_range(500.0f);
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