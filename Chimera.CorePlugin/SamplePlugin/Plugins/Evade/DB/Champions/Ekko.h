#pragma once
#include "../EvadeSpellData.h"

class Ekko
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Ekko, "Ekko Q");
		q_data->set_spell_hashes({ spell_hash("EkkoQ") })
			->set_object_names({ "EkkoQMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true)
			->set_missile_speed(1650.f)
			->set_radius(60.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1100.f);

		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Ekko, "Ekko Q2");
		q_data->set_spell_hashes({ spell_hash("EkkoQReturn") })
			->set_object_names({ "EkkoQReturn" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_is_end_pos_to_unit(true)
			->set_missile_speed(2300.f)
			->set_radius(100.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1100.f);

		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Ekko, "Ekko W");
		w_data->set_spell_hashes({ spell_hash("EkkoW") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_duration(4.5f)
			->set_missile_speed(2300.f)
			->set_radius(375.f)
			->set_range(1600.f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		//EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Ekko, "Ekko R");
		//spells.push_back(r_data);
		// TODO;
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