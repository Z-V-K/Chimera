#pragma once
#include "../EvadeSpellData.h"

class Qiyana
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Qiyana, "Qiyana Q");
		q_data
			->set_spell_hashes({ spell_hash("QiyanaQ") })
			//->set_object_names({ "QiyanaQ" }) 
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(FLT_MAX)
			->set_radius(70.0f)
			->set_range(470.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Qiyana, "Qiyana Q Grass");
		q_data
			->set_spell_hashes({ spell_hash("QiyanaQ_Grass") })
			->set_object_names({ "QiyanaQ_Grass" })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1600.0f)
			->set_radius(100.0f)
			->set_range(900.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Qiyana, "Qiyana Q Water");
		q_data
			->set_spell_hashes({ spell_hash("QiyanaQ_Water") })
			->set_object_names({ "QiyanaQ_Water" })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_hard_cc(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1600.0f)
			->set_radius(100.0f)
			->set_range(900.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Qiyana, "Qiyana Q Rock");
		q_data
			->set_spell_hashes({ spell_hash("QiyanaQ_Rock") })
			->set_object_names({ "QiyanaQ_Rock" })
			->set_type(EvadeSpellType::Line)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1600.0f)
			->set_radius(100.0f)
			->set_range(900.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Qiyana, "Qiyana R");
		r_data
			->set_spell_hashes({ spell_hash("QiyanaR") })
			->set_object_names({ "QiyanaRWallHitMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(2000.0f)
			->set_radius(140.0f)
			->set_collision_objects({ CollisionObject::Heroes, CollisionObject::GameWall, CollisionObject::YasuoWall })
			->set_range(875.0f);
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