#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

// TODO: Velkoz R
// TODO: Velkoz W missile after cast on_process_spell
class Velkoz
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Velkoz, "Velkoz Q");
		q_data
			->set_spell_hashes({ spell_hash("VelkozQ") })
			->set_object_names({ "VelkozQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1300.0f)
			->set_radius(50.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1100.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Velkoz, "Velkoz Q Split");
		q_data
			//->set_spell_hashes({ "VelkozQSplit" })
			->set_object_names({ "VelkozQMissileSplit" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(2100.0f)
			->set_radius(45.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1100.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Velkoz, "Velkoz W");
		w_data
			->set_spell_hashes({ spell_hash("VelkozW") })
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f + 0.75f)
			->set_missile_speed(1700.0f)
			->set_radius(87.5f)
			->set_range(1105.0f + 95.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_offset_start(-95.0f);
		// TODO;
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Velkoz, "Velkoz E");
		e_data
			->set_spell_hashes({ spell_hash("VelkozE") })
			//->objectNames({ "VelkozEMissile" })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f + 0.55f) // 0.55f travel time
			->set_missile_speed(FLT_MAX)
			->set_radius(225.0f)
			->set_range(800.0f);
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