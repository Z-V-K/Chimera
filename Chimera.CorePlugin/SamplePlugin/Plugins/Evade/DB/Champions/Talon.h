#pragma once
#include "../EvadeSpellData.h"

class Talon
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Talon, "Talon W");
		w_data
			->set_spell_hashes({ spell_hash("TalonW") })
			->set_object_names({ "TalonWMissileOne" })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(2000.0f)
			->set_radius(70.0f)
			->set_range(900.0f)
			->set_multiple_number(3)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_multiple_angle(10.92f * M_PI / 180.0f); // 15.69f * M_PI / 180.0f
		spells.push_back(w_data);

		w_data = new EvadeSpellData(CharacterHash::Talon, "Talon W Return");
		w_data
			->set_spell_hashes({ spell_hash("TalonWSpell") })
			->set_object_names({ "TalonWMissileTwo" })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_end_pos_to_unit(true)
			->set_add_bounding(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.0f)
			->set_missile_speed(2000.0f)
			->set_radius(50.0)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(20000.0f);
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