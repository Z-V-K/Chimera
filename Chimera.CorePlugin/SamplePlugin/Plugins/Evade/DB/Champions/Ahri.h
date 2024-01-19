#pragma once
#include "../EvadeSpellData.h"

class Ahri
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Ahri, "Ahri Q1");

		q_data->set_spell_hashes({ spell_hash("AhriQ") })
			->set_object_names({ "AhriQMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(900.f + 100.f)
			->set_radius(100.f)
			->set_delay(.25f)
			->set_missile_speed(1550.f)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_start_pos_updated_on_flash(true)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_danger_level(DangerLevel::Medium);

		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Ahri, "Ahri Q2");

		q_data
			->set_spell_hashes({ spell_hash("AhriQReturn") })
			->set_object_names({ "AhriQReturnMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(900.f + 100.f)
			->set_radius(100.f)
			->set_missile_speed(1900.f)
			->set_add_bounding(true)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_is_end_pos_to_unit(true)
			->set_danger_level(DangerLevel::Medium)
			->set_is_dangerous(true);

		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}


	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Ahri, "Ahri E");

		e_data->set_spell_hashes({ spell_hash("AhriE") })
			->set_object_names({ "AhriEMissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_range(1000.f)
			->set_radius(60.f)
			->set_missile_speed(1550.f)
			->set_is_range_fixed(true)
			->set_danger_level(DangerLevel::VeryHigh)
			->set_add_bounding(true)
			->set_is_hard_cc(true)
			->set_is_start_pos_updated_on_flash(true)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Minions, CollisionObject::Heroes })
			->set_is_dangerous(true);

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