#pragma once
#include "../EvadeSpellData.h"

class Khazix
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Khazix, "Khazix W");
		w_data->set_spell_hashes({ spell_hash("KhazixW") })
			->set_object_names({ "KhazixWMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(false)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1700.0f)
			->set_radius(50.0f) // wiki 70.0f
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_range(1025.0f);
		spells.push_back(w_data);

		w_data = new EvadeSpellData(CharacterHash::Khazix, "Khazix W Evolved");
		w_data->set_spell_hashes({ spell_hash("KhazixWLong") })
			->set_object_names({ "KhazixWMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1700.0f)
			->set_radius(50.0f) // wiki 70.0f
			->set_range(1025.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::Minions, CollisionObject::YasuoWall })
			->set_multiple_number(3)
			->set_multiple_angle(22.0f * M_PI / 180.0f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Khazix, "Khazix E");
		//spells.push_back(e_data);
		// TODO;
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