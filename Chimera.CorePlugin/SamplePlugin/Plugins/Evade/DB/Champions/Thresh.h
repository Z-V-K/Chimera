#pragma once
#include "../EvadeSpellData.h"

// TODO: R maybe
class Thresh
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Thresh, "Thresh Q");
		q_data
			->set_spell_hashes({ spell_hash("ThreshQ") })
			->set_object_names({ "ThreshQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.5f)
			->set_missile_speed(1900.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1100.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Thresh, "Thresh E");
		e_data
			->set_spell_hashes({ spell_hash("ThreshE") })
			//->objectNames({ "ThreshEMissile1" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_is_hard_cc(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.0f)
			->set_missile_speed(2000.0f)
			->set_radius(110.0f)
			->set_range(1075.0f)
			->set_offset_start(-537.5f);
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