#pragma once
#include "../EvadeSpellData.h"

class Sion
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Sion, "Sion Q");
		q_data
			->set_spell_hashes({ spell_hash("SionQ") })
			//->objectNames({ "SionQMissile"})
			->set_type(EvadeSpellType::Line)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_duration(2.0f)
			->set_missile_speed(FLT_MAX)
			->set_radius(200.0f)
			->set_range(800.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Sion, "Sion E");
		e_data
			->set_spell_hashes({ spell_hash("SionE") })
			->set_object_names({ "SionEMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1800.0f)
			->set_radius(80.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::YasuoWall })
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