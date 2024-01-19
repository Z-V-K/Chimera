#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Varus
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Varus, "Varus Q");
		q_data
			//->spellNames({ "VarusQSpell" }) // Not getting detected by ops since it doesn't matter in this case
			->set_object_names({ "VarusQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			//->isRangeFixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_missile_speed(1900.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_add_bounding(true)
			->set_range([](DetectedSpell* spell)
				{
					return std::min(spell->original_start_pos.distance(spell->original_end_pos), 1595.0f);
				});
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Varus, "Varus E");
		e_data
			->set_spell_hashes({ spell_hash("VarusE") })
			//->objectNames({ "VarusEMissile" })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.5f)
			->set_missile_speed(1750.0f)
			->set_radius(300.0f)
			->set_range(925.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Varus, "Varus R");
		r_data
			->set_spell_hashes({ spell_hash("VarusR") })
			->set_object_names({ "VarusRMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.2419f)
			->set_missile_speed(1500.0f)
			->set_radius(120.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
			->set_range(1370.0f);
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