#pragma once
#include "../EvadeSpellData.h"

class Seraphine
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Seraphine, "Seraphine Q");
		q_data
			->set_spell_hashes({ spell_hash("SeraphineQ") })
			//->objectNames({ "SeraphineQInitialMissile", "SeraphineQSecondaryMissile" })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(350.0f)
			->set_range(900.0f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Seraphine, "Seraphine Q Echo");
		q_data
			->set_spell_hashes({ spell_hash("SeraphineQCastEcho") })
			->set_type(EvadeSpellType::Circle)
			->set_is_dangerous(true)
			->set_duration(0.25f)
			->set_danger_level(DangerLevel::Medium)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(350.0f)
			->set_range(900.0f);
		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* e_data = new EvadeSpellData(CharacterHash::Seraphine, "Seraphine E");
		e_data
			->set_spell_hashes({ spell_hash("SeraphineE"), spell_hash("SeraphineECastEcho") })
			->set_object_names({ "seraphineemissile" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_delay(0.25f)
			->set_missile_speed(1200.0f)
			->set_radius(70.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1300.0f);
		spells.push_back(e_data);
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Seraphine, "Seraphine R");
		r_data
			->set_spell_hashes({ spell_hash("SeraphineR") })
			->set_object_names({ "SeraphineR" })
			->set_type(EvadeSpellType::MissileLine)
			->set_is_range_fixed(true)
			->set_add_bounding(true)
			->set_is_hard_cc(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Extreme)
			->set_delay(0.5f)
			->set_missile_speed(1600.0f)
			->set_radius(160.0f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(1200.0f);
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