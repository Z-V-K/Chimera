#pragma once
#include "../EvadeSpellData.h"

class Graves
{
private:
	static void load_q_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* q_data = new EvadeSpellData(CharacterHash::Graves, "Graves Q");
		q_data->set_spell_hashes({ spell_hash("GravesQLineSpell") })
			->set_object_names({ "GravesQLineMis" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_missile_speed(2000.f)
			->set_radius(100.f)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::GameWall })
			->set_range(820.f);
		spells.push_back(q_data);

		q_data = new EvadeSpellData(CharacterHash::Graves, "Graves Q2");
		q_data->set_spell_hashes({ spell_hash("GravesQReturn") })
			->set_object_names({ "GravesQReturn" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::Medium)
			->set_missile_speed(1600.f)
			->set_radius(100.f)
			->set_collision_objects({ CollisionObject::YasuoWall })
			->set_range(800.f);

		spells.push_back(q_data);
	}

	static void load_w_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* w_data = new EvadeSpellData(CharacterHash::Graves, "Graves W");
		w_data->set_spell_hashes({ spell_hash("GravesSmokeGrenade") })
			->set_object_names({ "GravesSmokeGrenadeBoom" })
			->set_type(EvadeSpellType::Circle)
			->set_duration(3.75f)
			->set_danger_level(DangerLevel::Low)
			->set_missile_speed(1500.f)
			->set_radius(200.f)
			->set_range(950.f);
		spells.push_back(w_data);
	}

	static void load_e_data(std::vector<EvadeSpellData*>& spells)
	{
	}

	static void load_r_data(std::vector<EvadeSpellData*>& spells)
	{
		EvadeSpellData* r_data = new EvadeSpellData(CharacterHash::Graves, "Graves R");
		r_data->set_spell_hashes({ spell_hash("GravesChargeShot") })
			->set_object_names({ "GravesChargeShot" })
			->set_type(EvadeSpellType::MissileLine)
			->set_add_bounding(true)
			->set_is_range_fixed(true)
			->set_is_dangerous(true)
			->set_danger_level(DangerLevel::High)
			->set_missile_speed(2100.f)
			->set_radius(100.f)
			->set_collision_objects({ CollisionObject::YasuoWall, CollisionObject::Heroes })
			->set_range(1100.f);

		//TODO; end explosion
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