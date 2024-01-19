#pragma once
#include "../EvadeSpellData.h"
#include "../../SpellDetector/DetectedSpells/DetectedSpell.h"

class Urgot
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Urgot, "Urgot Q");
		q_data
			->set_spell_hashes({ spell_hash("UrgotQ") })
			//->objectNames({ "UrgotQMissile"})
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.55f)
			->set_missile_speed(FLT_MAX)
			->set_radius(210.0f)
			->set_range(800.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Urgot, "Urgot E");
		e_data
			->set_spell_hashes({ spell_hash("UrgotE") })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.45f)
			->set_missile_speed(1200.0f) // + 100% mov speed
			->set_radius(100.0f)
			->set_range(650.0f)
			->set_collision_objects({ CollisionObject::Heroes })
			->set_missile_speed([](DetectedSpell* spell)
			{
				return 1200.0f + spell->source->get_movement_speed();
			})
			->set_duration([](DetectedSpell* spell)
			{
				return spell->get_range() / spell->spell_data->missile_speed(spell);
			});
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Urgot, "Urgot R");
		r_data
			->set_spell_hashes({ spell_hash("UrgotR") })
			->set_object_names({ "UrgotR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.5f)
			->set_missile_speed(3200.0f)
			->set_radius(80.0f)
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